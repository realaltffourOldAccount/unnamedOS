# unnamedOS

An OS built from scratch for the purposes of learning.

## Getting started

These instructions will get you a copy of the project for testing and development.

### Prerequisites

Using ```nix```:

```shell
$ nix-shell
```

#### Install prerequisites of the project on ```ubuntu```:

```shell
$ sudo apt install build-essential cmake nasm gcc qemu
```

And to be able to build the compiler (optional, binaries of the compiler are included):

```shell
$ sudo apt install bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libcloog-isl-dev libisl-dev
```

#### Install prerequisites of the project on ```arch```:

```shell
$ pacman -S gcc make cmake extra/nasm qemu
```

And to be able to build the compiler (again, optional, binaries of the compiler are included):

```shell
$ pacman -S bison flex gmp mpc mpfr texinfo
```

#### Install prerequisites of the project on ```gentoo```:

```shell
$ sudo emerge --ask sys-devel/gcc sys-devel/make dev-lang/nasm dev-util/cmake app-emulation/qemu
```

And to be able to build the compiler (optional, binaries of the compiler are included):

```shell
$ sudo emerge --ask sys-devel/bison sys-devel/flex dev-libs/gmp dev-libs/mpc dev-libs/cloog dev-libs/isl
```

### Installing

To build the project using nix:

```shell
$ nix-shell
$ ./build.sh
```

To build the compiler (not needed, as long as the compiler binaries aren't cleaned):

```shell
$ ./compilers/<COMPILER_NAME>/install.sh
```

### Cleaning the directory

To clean the project directory:

```shell
$ ./clean.sh
```

Note: This does NOT clean the compiler binaries.

To clean the compiler directory(NOT RECOMMENDED):

```shell
$ ./compilers/<COMPILER_NAME>/clean.sh
```
Note: This renders the project unbuildable.

### Running the project on qemu

```shell
$ ./qemu.sh
```

## Contributing

Feel free to contribute to the project!
TODO: Add an actual CONTRIBUTING.md file.

## Authors

* **Ayham Mamoun** - *Initial Work* - [Profile](https://gitlab.com/ayhamaboualfadl)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE) file for details.
