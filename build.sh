#!/bin/sh

# Get the directory of the script.
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Get the choosen compiler to build with.
COMPILER=$(./default-compiler.sh)

# Build the compiler.
set -e
$DIR/compilers/$COMPILER/install.sh

# Build unnamedOS.
set -e
. $DIR/compile.sh
