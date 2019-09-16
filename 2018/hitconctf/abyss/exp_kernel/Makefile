TARGET := hack.bin

SRCS := entry.s kernel_main.c 
OBJS := hypercall.o mm.o utils.o string.o
DEPS := $(wildcard ./**/*.d)

CFLAGS := -Wall -fPIE -pie -masm=intel -nostdlib 
LDFLAGS := -ffreestanding -fno-builtin -Tlinker.script

.PRECIOUS: %.o
all: $(TARGET)

%.bin: $(SRCS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -Xlinker --oformat=binary $(LDFLAGS)

%.o: %.s
	$(AS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@


.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET) $(DEPS)

FORCE:

-include *.d
