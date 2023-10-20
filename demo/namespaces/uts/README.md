# UTS namespaces

[&laquo; Back to the namespace demos](../)

## Abstract

This directory contains a sample application to demonstrate how UTS namespaces work. UTS namespaces allow you to
change the hostname for a single process while leaving other processes unaffected.

# How it works

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

## Testing

Run the compiled `demo_namespaces_uts` program as root (see [compilation instructions](../../README.md)).

```bash
$ ./demo_namespaces_uts
$ hostname
test
```

As you can see, the hostname for this shell has been changed to `test`. You can exit the shell with `Ctrl+D`.