# Custom Darwin SDK

> An alternative to Apple's offical SDKs for Darwin

> Currently supports x86_64, armv6, armv7, and armv7s

## Requirements:

- LLVM+Clang
- [ld64](https://github.com/tpoechtrager/cctools-port) (On Linux, ld64 should be in path as `ld64.ld64`)

## Building:

To build a universal SDK

```sh
make
```

To build an SDK for a single architecture

```sh
make ARCHS='armv7'
```

To build the tests

```sh
make tests
```
