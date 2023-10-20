#!/bin/bash

set -e

wget -c https://dl-cdn.alpinelinux.org/alpine/v3.18/releases/x86_64/alpine-minirootfs-3.18.4-x86_64.tar.gz
dd if=/dev/zero of=container.img  bs=50M  count=1
mkdir -p build
mkfs.ext4 container.img
mount container.img build
cd build
tar -xvvzf ../alpine-minirootfs-3.18.4-x86_64.tar.gz
cd ..
umount build
rm -rf build
