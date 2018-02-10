# Abstract

This directory contains a sample application to demonstrate how mount namespaces work.

## Recommended reading

- [Under the hood of Docker](https://pasztor.at/blog/under-the-hood-of-docker)
- [Mount namespaces and shared subtrees](https://lwn.net/Articles/689856/)

## Detailed modus operandi

1. First of all, the program launches a function (`child`) in a separate namespace:
   ```c
   pid_t childPid = clone(
       child,
       stackTop,
       CLONE_NEWNS | SIGCHLD,
       {}
   );
   ```
2. The child is launched in a separate process, which is now in a new namespace. Mount namespaces
   are implicit, so no need to declare a namespace above.
3. However, the mount points are still shared with the parent namespace, so we now read the list of
   mount points from `/proc` using `setmntent`.
4. For every mount point, we remount the mount points as *slaves*:
   ```c
   mount(nullptr, mountEntry->mnt_dir, mountEntry->mnt_type, MS_REC|MS_SLAVE, nullptr)
   ```
   Mounting as a slave means that we can now safely unmount or remount the mount point without
   affecting the parent namespace.
