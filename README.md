# Linux containers explained with code

This is a demo container runtime to showcase how various Linux features, like namespaces, are used to create containers.
Each folder contains a demo and a description on how it works so you can follow along.

![](screenshot.png)

## Contents

This project is structured into two parts, each with a full description:

- [Individual demos](demo)
- [Complex container runtime](runtime)

## Building the source

### Warning

This code is experimental and may destroy your host operating system. **Please run it on a virtual machine / dedicated
WSL instance.**

### Build tools

In order to build these demos, you will need a Linux-based C++ toolchain and cmake installed. On Ubuntu 22.04, you can
install these packages:

```bash
$ sudo apt install build-essential cmake
```

### Dependencies

In order to compile these demos, you will need to install the header files for libcap, libseccomp and zlib. On Ubuntu
you can do this by running:

```bash
$ sudo apt install libcap-ng-dev libseccomp-dev zlib1g-dev
```

### Compiling

Once you have installed the dependencies, you can compile the source by running:

```bash
cmake .
make
```

Now you can run the binaries in the individual demo folders.
