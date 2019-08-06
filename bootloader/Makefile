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
.SUFFIXES: .bin .S

all: boot.bin 

boot.bin: 
	nasm $(ASMFLAGS) $(BOOT0_SRC) -o $@
	nasm $(ASMFLAGS) $(BOOT1_SRC) -o $@
	cat boot0.bin boot1.bin > boot.bin
	rm -f boot0.bin
	rm -f boot1.bin

clean:
	rm -f boot0.bin
	rm -f boot1.bin
	rm -f $(OBJS) *.0 */*.o */*/*.o

install: install-bootloader

install-bootloader: boot.bin
	cp boot.bin $(DESTDIR)$(BOOTLOADERDIR)
