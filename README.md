# Custom Darwin SDK

> An alternative to Apple's offical SDKs for Darwin

> Currently supports x86_64 and arm32

## Requirements:

- LLVM+Clang
- [ld64](https://github.com/tpoechtrager/cctools-port)

## Building:

To build an SDK for x86_64

```sh
make
```

To build an SDK for another architecture

```sh
make CC='clang -target armv6-apple-darwin'
```

To build the tests

```sh
make tests
```
