# Shard C Library 2

This is my second attempt at creating a usable C library.

## Build instructions

This project uses Google's [GN](https://gn.googlesource.com/gn#getting-a-binary) build system, because it works great for wierd projects like this and Chromium. To generate Ninja build files, run this command:
```shell
gn gen out
```
If you want to use an IDE for editing/debugging, use the `--ide` flag. In my testing, these projects can't be built from the IDE, so run `ninja -C <output directory>` to build before you debug.
