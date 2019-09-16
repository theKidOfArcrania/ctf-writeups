#include "mm.h"
#include "hypercall.h"
#include "string.h"
#include "utils.h"

#include <linux/kvm.h>


#define _OFFSET(v, bits) (((uint64_t)(v) >> (bits)) & 0x1ff)
#define PML4OFF(v) _OFFSET(v, 39)
#define PDPOFF(v) _OFFSET(v, 30)
#define PDOFF(v) _OFFSET(v, 21)
#define PTOFF(v) _OFFSET(v, 12)

#define INVALID ((uint64_t)-1)

#define VMFD 4
#define HADDR_START_ADDR (1<<25)

static inline uint64_t* get_pml4_addr() {
  uint64_t pml4;
  asm("mov %[pml4], cr3" : [pml4]"=r"(pml4));
  return (uint64_t*) (pml4 | KERNEL_BASE_OFFSET);
}

// Stub to call actual kernel
void* kmalloc(uint64_t size, uint64_t padding) {
  return ((void* (*)(uint64_t, uint64_t))(0x15e0 | KERNEL_BASE_OFFSET))(size, padding);
}

// Stub to call actual kernel
void kfree(void *mem) {
  ((void (*)(void*))(0x1577 | KERNEL_BASE_OFFSET))(mem);
}

uint32_t physical(void *vaddr_) {
  uint64_t vaddr = (uint64_t)vaddr_;
  if (!((uint64_t)vaddr & KERNEL_BASE_OFFSET))
    hp_panic("mm.c#physical(): Not kernel memory address");
  vaddr = vaddr ^ KERNEL_BASE_OFFSET;
  if (vaddr >> 32)
    hp_panic("mm.c#physical(): Hyper address cannot fit into 32-bit integer!");
  return (uint32_t)vaddr;
}

/* if vaddr is already mapping to some address, overwrite it. */
void *create_mmap(void* vaddr_, void* paddr_) {
  uint64_t vaddr = (uint64_t) vaddr_;
  uint64_t paddr = (uint64_t) paddr_ & ~KERNEL_BASE_OFFSET;
  uint64_t* pml4 = get_pml4_addr(), *pdp, *pd, *pt;
#define PAGING(p, c) do { \
    if(!(*p & PDE64_PRESENT)) { \
      c = (uint64_t*) kmalloc(PAGE_SIZE, PAGE_SIZE); \
      *p = PDE64_PRESENT | PDE64_RW | PDE64_USER | physical(c); \
    } else { \
      c = (uint64_t*) ((*p & -0x1000) | KERNEL_BASE_OFFSET); \
    } \
  } while(0);
  PAGING(&pml4[PML4OFF(vaddr)], pdp);
  PAGING(&pdp[PDPOFF(vaddr)], pd);
  PAGING(&pd[PDOFF(vaddr)], pt);
#undef PAGING
  pt[PTOFF(vaddr)] = PDE64_PRESENT | PDE64_USER | PDE64_RW | paddr;
  return vaddr_;
}

int next_slot = 1;
uint64_t next_memoff = 0;
void *create_hmmap(void* haddr_, uint64_t size) {

  void* vaddr_ = (void*)(EXT_MEM_OFFSET + next_memoff);
  uint64_t paddr = HADDR_START_ADDR + next_memoff;
  uint64_t haddr = (uint64_t)haddr_;

  struct kvm_userspace_memory_region *region = kmalloc(sizeof(*region), 0);
  region->slot = next_slot;
  region->flags = 0;
  region->guest_phys_addr = paddr;
  region->memory_size = size;
  region->userspace_addr = haddr;

  next_memoff += size;
  next_slot++;

  int res = hp_ioctl(VMFD, KVM_SET_USER_MEMORY_REGION, region);
  if (res < 0) {
    hp_exit(res);
    hp_panic("mm.c#create_hmmac: hp_ioctl failed");
  }

  kfree(region);

  uint64_t pages = size / PAGE_SIZE;
  while (pages --> 0)
    create_mmap(vaddr_ + pages * PAGE_SIZE, (void*)(paddr + pages * PAGE_SIZE));
  return vaddr_;
}


void *memdup(void *src, size_t size) {
  void *dst = kmalloc(size, 0);
  memcpy(dst, src, size);
  return dst;
}

