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

BOOT0_OBJS= \
$(BOOT0_ARCH_OBJ) \

.PHONY: all clean install install-headers install-bootloader
.SUFFIXES: .o .c .S

boot0.bin: $(BOOT0_OBJS)	
	$(LD) -o boot0.bin -e init $(BOOT0_OBJS)

.S.o:
	$(AS) -o $@ $<

clean:
	rm -f boot0.bin boot1.bin
	rm -f $(OBJS) *.o */*.o */*/*.o

install: install-bootloader

install-bootloader: boot0.bin

-include $(BOOT1_OBJS:.o=.d)
