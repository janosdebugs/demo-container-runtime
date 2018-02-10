# Abstract

This directory contains a sample application to demonstrate how network namespaces work.

# Warning

THIS CODE IS INTENDED FOR DEMONSTRATION PURPOSES ONLY AND IS NOT SUITABLE FOR A PRODUCTION ENVIRONMENT!

# Recommended reading

- [Under the hood of Docker](https://pasztor.at/blog/under-the-hood-of-docker)

# Detailed modus operandi

1. First of all, the program launches a function (`child`) in a separate namespace:
   ```c
   pid_t childPid = clone(
       child,
       stackTop,
       CLONE_NEWNS | CLONE_NEWNET | SIGCHLD,
       {}
   );
   ```
2. The child is launched in a separate process, which is now in a new namespace. Since the network
   namespace is declared above, it does not inherit any of the hosts network devices, it must create
   its own.
