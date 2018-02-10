# Abstract

This directory contains a sample application to demonstrate how UTS namespaces work.

## Recommended reading

- [Under the hood of Docker](https://pasztor.at/blog/under-the-hood-of-docker)

## Detailed modus operandi

1. First of all, the program launches a function (`child`) in a separate namespace:
   ```c
   pid_t childPid = clone(
       child,
       stackTop,
       CLONE_NEWNS | CLONE_NEWUTS | SIGCHLD,
       {}
   );
   ```
2. The child is launched in a separate process, which is now in a new namespace. We can now safely
   change the host name without affecting the parent:
   ```c
   sethostname("test", 4)
   ```
