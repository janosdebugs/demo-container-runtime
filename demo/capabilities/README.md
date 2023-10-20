# Capabilities demo

[&laquo; Back to the demos](../)

## Abstract

This directory contains a demo program that launches a bash shell without any capabilities. When you run it, you should
find that even though you are root, you cannot do the things root normally does.

## How it works

1. The program uses `capng_clear()` to remove all capabilities from the current process.
2. The program then uses `capng_apply()` to apply the chosen capabilities.
3. The program then replaces itself with a shell.

## Testing

Once you built the binary ([see instructions](../../README.md)) you can run `demo_cap` as root to check the
capabilities:

```bash
$ cat /proc/$$/status|grep Cap
CapInh: 0000000000000000
CapPrm: 000001ffffffffff
CapEff: 000001ffffffffff
CapBnd: 000001ffffffffff
CapAmb: 0000000000000000

$ ./demo_cap

$ cat /proc/$$/status|grep Cap   # <- This is now a restricted shell
CapInh: 0000000000000000
CapPrm: 0000000000000000
CapEff: 0000000000000000
CapBnd: 0000000000000000
CapAmb: 0000000000000000
```

As you can see, once the shell is running inside `demo_cap`, no capabilities are left. You can also try to do something
you would normally be able to do a root:

```bash
$ tcpdump
tcpdump: eth0: You don't have permission to capture on that device
(socket: Operation not permitted)
```

You can exit the restricted shell by hitting `Ctrl+D`.