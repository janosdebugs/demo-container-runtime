# Network namespaces

[&laquo; Back to the namespace demos](../)

## Abstract

This directory contains a sample application to demonstrate how network namespaces work. Network namespaces allow a 
process to see a separate set of network interfaces than their host OS.

## How it works

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

## Testing

You can test this demo by running the `demo_namespaces_net` program as root (see [compilation instructions](../../README.md)).

```
# ./demo_namespaces_net
```

You can then run `ip addr` and should see no network interfaces apart from the loopback:

```
# ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```

You can now exit the restricted shell with `Ctrl+D`.