# Mount namespaces

[&laquo; Back to the namespace demos](../)

## Abstract

This directory contains a sample application to demonstrate how mount namespaces work. Mount namespaces allow processes
to see a separate set of mounts than the host OS.

## Warning

Do not run this code on your laptop/work machine! Use a VM!

## Recommended reading

- [Mount namespaces and shared subtrees](https://lwn.net/Articles/689856/)

## How it works

1. First, the program launches a function (`child`) in a separate namespace:
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

## Testing

You can run `demo_namespaces_mount` to remount all volumes as slaves (see [compilation instructions](../../README.md)).
This allows you to unmount/remount all mount  points independently of the "host" operating system.

```
# ./demo_namespaces_mount
Remounting / as slave...
Remounting /init as slave...
Remounting /dev as slave...
Remounting /dev/pts as slave...
Remounting /dev/shm as slave...
Remounting /dev/hugepages as slave...
Remounting /dev/mqueue as slave...
...
Starting bash inside a mount namespace. You should be able to safely unmount any mount point...
```

Now you can unmount a directory independently of the host. Remember that you must unmount any mount points in
subdirectories first.

```
# for mountpoint in $(mount| awk ' {print $3 }'|sort -r); do echo $mountpoint; umount $mountpoint; done
...
umount: /: target is busy.
```

The last error message is normal as the root filesystem is required. In the full containerization demo, you can
take a look how the root filesystem is replaced to work around this.

If you now try to run `mount`, you'll get an error message:

```
# mount
mount: failed to read mtab: No such file or directory
```

If you hit `Ctrl+D`, however, you are back in your previous shell and your mount points should also be back to normal.