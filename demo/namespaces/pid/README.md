# PID namespaces

[&laquo; Back to the namespace demos](../)

## Abstract

This directory contains a sample application to demonstrate how PID namespaces work. PID namespaces allow a process to
see a separate set of processes than their host OS.

## How it works

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

## Testing

You can run the compiled `demo_namespace_pid` program as root (see [compilation instructions](../../README.md)).

```
# ./demo_namespace_pid
Changing the /proc mountpoint to slave...
Remounting /proc so PID namespaces take effect...
Launching bash in a PID namespace. ps auwfx should not show any processes outside the container.

# ps auwfx
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.0   5044  3988 pts/5    S    14:10   0:00 /bin/bash
root           8  0.0  0.0   7480  3204 pts/5    R+   14:10   0:00 ps auwfx
```

You can now exit the restricted shell by pressing `Ctrl+D`.