# Seccomp

[&laquo; Back to the demos](../)

## Abstract

The code in this folder demonstrates how seccomp works. Seccomp lets you restrict system calls.

## How it works

1. First, `seccomp_init` is called with the default policy as a parameter:
   ```c
   ctx = seccomp_init(SCMP_ACT_ALLOW)
   ```
   In production you would, of course, use `SCMP_ACT_KILL` as a default policy.
2. Next, all exceptions to the default policy are added, such as:
   ```c
   seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(bind), 0);
   ```
3. Finally, the seccomp profile is applied and the current process is locked down:
   ```
   seccomp_load(ctx);
   ```
   Now the seccomp profile is active and the blocked syscalls (here: `bind`) will result in the
   seccomp engine acting.

## Testing

You can test te `demo_seccomp` application by running it:

```
# ./demo_seccomp
Now running bash with the bind syscall disabled. Try running telnet google.com 80 !
# telnet google.com 80
Bad system call
```

As you can see, the `bind` system call has been restricted and telnet doesn't work. You can exit the restricted shell
by pressing `Ctrl+D`.