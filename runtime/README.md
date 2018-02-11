# Abstract

This is a container runtime to demonstrate how containers work. It mounts a simple, ext4 container image from a file
and allows executing a shell in it.

# Warning

THIS CODE IS INTENDED FOR DEMONSTRATION PURPOSES ONLY AND IS NOT SUITABLE FOR A PRODUCTION ENVIRONMENT!

# Detailed modus operandi

This runtime declares an abstract class called `SeparationPlugin` that can be extended to add plugins. Each plugin
can do three things:

1. Execute code before the `clone()` command happens
2. Return flags for the `clone()` command (for e.g. to open namespaces)
3. Execute code after the `clone()`, but before the `execv` command.

The following plugins are added for demonstration:

- [PidNamespaceSeparationPlugin](plugin/PidNamespaceSeparationPlugin.h): Initializes the PID namespace.
- [MountNamespaceSeparationPlugin](plugin/MountNamespaceSeparationPlugin.h): Remounts all mounts as slaves after `clone()`.
- [NetNamespaceSeparationPlugin](plugin/NetNamespaceSeparationPlugin.h): Initializes the network namespace.
- [UtsNamespaceSeparationPlugin](plugin/UtsNamespaceSeparationPlugin.h): Initializes the UTS (hostname) namespace.
- [CleanMountsSeparationPlugin](plugin/CleanMountsSeparationPlugin.h): Unmounts everything except for the root filesystem.
- [MountImageSeparationPlugin](plugin/MountImageSeparationPlugin.h): Mounts an image file through a loop device, then chroots into the folder.

Needless to say, there are many more things that could and should be added here, but this is only intended as a
demonstration.

# Usage

If you want to test this runtime, please do so on a separated virtual machine. This code is very experimental and is
not guaranteed to leave your machine in a workable state.

First of all, you will need at least cmake 3.5 and libseccomp headers installed. Then you need to compile the source:

```
cmake .
make
```

This will generate a number of binaries, among others the `demo_runtime` binary.

Next, you will need a container image. This is basically an ext4 filesystem in a binary file. The
[testcontainer](../testcontainer) folder contains a build.sh file to generate one with Alpine Linux on it.

Once you have the image, you just have to run the container:

```
sudo ./demo_runtime container.img /bin/sh
```
