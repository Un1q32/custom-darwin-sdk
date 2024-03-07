# Custom Darwin SDK

> An alternative to Apple's offical SDKs for Darwin

> Currently supports x86_64, x86_64h, armv6, armv7, armv7s, and armv7k

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
make ARCHS='x86_64'
```

To build the tests

```sh
make tests
```
