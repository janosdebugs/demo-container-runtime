# Abstract

This directory contains a sample application to demonstrate how PID namespaces work.

## Recommended reading

- [Under the hood of Docker](https://pasztor.at/blog/under-the-hood-of-docker)

## Detailed modus operandi

1. First of all, the program launches a function (`child`) in a separate namespace:
   ```c
   pid_t childPid = clone(
       child,
       stackTop,
       CLONE_NEWNS | CLONE_NEWPID | SIGCHLD,
       {}
   );
   ```
2. The child is launched in a separate process, which is now in a new namespace. It is running in
   its own PID namespace, but it still has the `/proc` mountpoint from the parent.
3. We must first make the `/proc` mount a slave (see [mount namespaces](../mount) for details):
   ```c
   mount("none", "/proc", nullptr, MS_REC|MS_SLAVE, nullptr)
   ```
4. Now that we have an independent `/proc` mount point, we can remount it, putting the PID namespace
   to work:
   ```c
   mount("proc", "/proc", "proc", 0, nullptr)
   ```
