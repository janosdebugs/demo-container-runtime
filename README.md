# Linux containers explained with code

This is a demo container runtime to showcase how various Linux features, like namespaces, are used to create containers.
Each folder contains a demo and a description on how it works so you can follow along.

![](screenshot.png)

## Start learning

This project is structured into two parts, each with a full description:

1. [Individual demos](demo)
2. [Complex container runtime](runtime)

Explore the folders and read the guides in each of them.

## Try it for yourself

If you want to try it out for yourself, you have to build it from source. However, note that this code is experimental.
It should be safe to run, but to be sure, **please run it on a Linux virtual machine / dedicated WSL instance.**

### Step 1: Build tools

In order to build these demos, you will need a Linux-based C++ toolchain and cmake installed. On Ubuntu 22.04, you can
install these packages:

```bash
$ sudo apt install build-essential cmake
```

### Step 2: Dependencies

In order to compile these demos, you will need to install the header files for libcap, libseccomp and zlib. On Ubuntu
you can do this by running:

```bash
$ sudo apt install libcap-ng-dev libseccomp-dev zlib1g-dev
```

### Step 3: Compiling

Once you have installed the dependencies, you can compile the source by running:

```bash
$ cmake .
$ make
```

Congratulations! Now each demo has a runnable binary in the folder. Follow the instructions in the individual folders
to run them.

## License

This repository is licensed under the
[Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International](LICENSE) license.

### You are free to:

- **Share** — copy and redistribute the material in any medium or format

The licensor cannot revoke these freedoms as long as you follow the license terms.

### Under the following terms:

- **Attribution** - You must give appropriate credit , provide a link to the license, and indicate if changes were made . You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
- **NonCommercial** - You may not use the material for commercial purposes .
- **NoDerivatives** - If you remix, transform, or build upon the material, you may not distribute the modified material.
- **No additional restrictions** - You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

### Notices:

You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation .

No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material.
