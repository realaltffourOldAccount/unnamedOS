# Projects lists
#SYSTEM_HEADER_PROJECTS="bootloader lib/libc kernel"
#PROJECTS="bootloader lib/libc kernel"

SYSTEM_HEADER_PROJECTS="lib/libc kernel"
PROJECTS="lib/libc kernel"

# Host configuration
export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

# Tools
export CC=${HOST}-gcc
export AR=${HOST}-ar
export AS=${HOST}-as
export ASM=nasm

# Generic Configuration.
export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

# Bootloader Configuration.
export BOOTLOADERDIR=/
export FILESYS=./default-fs.sh
export BOOTMODEM=./default-bootmodem.sh

# Compiler Configuration.
export CFLAGS='-O2 -g'
export CPPFLAGS=''
export ASMFLAGS=''

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/build/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rathers than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
    export CC="$CC -isystem=$INCLUDEDIR"
fi
