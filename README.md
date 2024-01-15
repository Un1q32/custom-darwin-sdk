# Custom iOS SDK

> An alternative to Apple's offical iOS SDK for 32-bit devices

## Requirements:

- LLVM+Clang
- [ld64](https://github.com/tpoechtrager/cctools-port)

## Building:

To build an SDK for armv7

```sh
make
```

To build an SDK for another architecture

```sh
make CC='clang -target armv7s-apple-ios'
```

To build the tests

```sh
make tests
```
