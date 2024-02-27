# Custom Darwin SDK

> An alternative to Apple's offical SDKs for Darwin

> Currently supports x86_64 and arm32

## Requirements:

- LLVM+Clang
- [cctools/ld64](https://github.com/tpoechtrager/cctools-port) (On Linux, ld64 should be in path as `ld64.ld64`)

## Building:

To build a universal SDK

```sh
make
```

To build an SDK for a single architecture

```sh
make CC='clang -target armv7-apple-darwin10'
```

To build the tests

```sh
make tests
```
