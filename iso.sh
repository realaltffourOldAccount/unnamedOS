#!/bin/sh

# Make sure that the OS is build beforehand.
set -e
. ./build.sh

# Set-up the directory structure.
mkdir -p build
mkdir -p build/isodir
mkdir -p build/isodir/boot/
mkdir -p build/isodir/boot/grub

# Copy the files to the correct location.
cp build/sysroot/boot/unnamedOS.kernel build/isodir/boot/unnamedOS.kernel

cat > build/isodir/boot/grub/grub.cfg << EOF
menuentry "unnamedOS" {
    multiboot /boot/unnamedOS.kernel
}
EOF

# Generate the ISO.
grub-mkrescue -o unnamedOS.iso build/isodir
