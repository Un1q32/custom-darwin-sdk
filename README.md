# Custom Darwin SDK

> An alternative to Apple's offical SDKs for Darwin

> Currently supports i386, x86_64, x86_64h, armv6, armv7, armv7s, and armv7k

## Requirements:

- LLVM+Clang
- [ld64](https://github.com/tpoechtrager/cctools-port) (On non-macOS systems, ld64 should be in path as `ld64.ld64`)

## Building:

To build a universal SDK

```sh
make release
```

To build an SDK for a single architecture

```sh
make release ARCHS='x86_64'
```

To build the tests

```sh
make tests
```

To easily use the SDK, add the bin folder to your $PATH

```sh
x86_64-apple-darwin-cc something.c -lc # libc isn't linked by default
```
