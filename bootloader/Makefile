DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?= -O2 -g
CPPFLAGS?=
ASMFLAGS?=

DESTDIR?=

ASMFLAGS:=$(ASMFLAGS) -f bin

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

ASMFLAGS:=$(ASMFLAGS) $(BOOTLOADER_ARCH_ASMFLAGS)

BOOT0_SRC=\
$(BOOT0_ARCH_SRC)\

BOOT1_SRC=\
$(BOOT1_ARCH_SRC)\

.PHONY: all clean install install-headers install-bootloader
.SUFFIXES: .o .bin .S .c

boot0.bin: $(BOOT0_OBJS)

boot1.bin: $(BOOT1_OBJS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f boot0.bin boot1.bin
	rm -f $(OBJS) *.o */*.o */*/*.o

install: install-bootloader

install-bootloader: boot0.bin boot1.bin

