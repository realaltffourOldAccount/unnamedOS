SYSTEM_HEADER_PROJECTS="bootloader lib/libc kernel"
PROJECTS="bootloader lib/libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export CC=${HOST}-gcc
export AR=${HOST}-ar
export AS=${HOST}-as
export ASM=nasm

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export BOOTLOADERDIR=/
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

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
