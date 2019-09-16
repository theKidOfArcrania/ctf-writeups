#ifndef _MM_H
#define _MM_H

#include <inttypes.h>
#include <sys/types.h>

/* 64-bit page * entry bits */
#define PDE64_PRESENT 1
#define PDE64_RW (1 << 1)
#define PDE64_USER (1 << 2)
#define PDE64_ACCESSED (1 << 5)
#define PDE64_DIRTY (1 << 6)
#define PDE64_PS (1 << 7)
#define PDE64_G (1 << 8)

#define KERNEL_BASE_OFFSET (0x8000000000llu)
#define EXT_MEM_OFFSET (0xc000000000llu)

#define PAGE_SIZE_BITS 12
#define PAGE_SIZE (1<<PAGE_SIZE_BITS)

void *kmalloc(uint64_t size, uint64_t padding);
void kfree(void *mem);
void *create_mmap(void *vaddr, void *paddr);
void *create_hmmap(void *haddr, uint64_t size);
uint32_t physical(void *kmem);
void *memdup(void *src, size_t size);


#endif
