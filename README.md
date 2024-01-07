# Custom iOS SDK

> Write programs for 32bit iOS without Apple's SDK

Probobly won't ever go anywhere

## Building:

```sh
make [CROSS_PREFIX=armv7-apple-darwin11-]
```

## Usage:

```sh
armv7-apple-darwin11-cc hello.c src/libc.a -Iinclude
```
