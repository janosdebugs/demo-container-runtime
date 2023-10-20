# Containerization demo

[&ldquo; Back](../)

## Abstract

This is a container runtime to demonstrate how containers work. It mounts a simple, ext4 container image from a file
and allows executing a shell in it.

## Warning

This code is experimental and may harm your system. Please run it in a VM or WSL instance!

## How it works

This runtime declares an abstract class called `SeparationPlugin` that can be extended to add plugins. Each plugin
can do three things:

1. Execute code before the `clone()` command happens.
2. Return flags for the `clone()` command (for e.g. to open namespaces).
3. Execute code after the `clone()`, but before the `execv` command.

The following plugins are added for demonstration:

- [PidNamespaceSeparationPlugin](plugin/PidNamespaceSeparationPlugin.h): Initializes the PID namespace.
- [MountNamespaceSeparationPlugin](plugin/MountNamespaceSeparationPlugin.h): Remounts all mounts as slaves after `clone()`.
- [NetNamespaceSeparationPlugin](plugin/NetNamespaceSeparationPlugin.h): Initializes the network namespace.
- [UtsNamespaceSeparationPlugin](plugin/UtsNamespaceSeparationPlugin.h): Initializes the UTS (hostname) namespace.
- [MountImageSeparationPlugin](plugin/MountImageSeparationPlugin.h): Mounts an image file through a loop device, then chroots into the folder.

Needless to say, there are many more things that could and should be added here, but this is only intended as a
demonstration.

## Testing

First, build the demos ([see instructions](../README.md)). Then, you will need a container image.
This is basically an ext4 filesystem in a binary file. The [testcontainer](../testcontainer) folder contains the necessary
instructions and files.

Once you have the image, you just have to run the container as root:

```bash
$ ./demo_runtime ../testcontainer/container.img /bin/sh
/ #
```

You are now in a container. You can, for example, test that you don't see any network interfaces apart from the
loopback:

```bash
/ # ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```

You will also see that the mount points have disappeared:

```bash
/ # mount
/dev/loop5 on / type ext4 (rw,relatime)
proc on /proc type proc (rw,relatime)
```

And the processes are also not visible:

```bash
/ # ps auwfx
PID   USER     TIME   COMMAND
    1 root       0:00 /bin/sh
    7 root       0:00 ps auwfx
```

You can close the container by hitting `Ctrl+D`.