# Abstract

The code in this folder demonstrates how seccomp works.

# Warning

THIS CODE IS INTENDED FOR DEMONSTRATION PURPOSES ONLY AND IS NOT SUITABLE FOR A PRODUCTION ENVIRONMENT!

# Detailed modus operandi

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