#!/bin/bash

set -e

dd if=/dev/zero of=container.img  bs=10M  count=1
mkdir -p build
mkfs.ext4 container.img
mount container.img build
cd build
tar -xvvzf ../alpine-minirootfs-3.7.0-x86_64.tar.gz
cd ..
umount build
rm -rf build
