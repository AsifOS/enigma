#!/usr/bin/env zsh

make
qemu-system-i386 -m 512M -cdrom build/bin/asifos.iso