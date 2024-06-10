# Uniq's Darwin Libc

> An alternative to Apple's offical SDKs for Darwin systems

> Easily create static binaries

> Currently supports i386, x86_64, x86_64h, armv6, armv7, armv7s, armv7k, arm64, and arm64e (arm64 and arm64e are untested)

## Requirements: (macOS)

- Just install the Xcode Command Line Tools

## Requirements: (Linux, BSD, etc.)

- Clang (GCC recieves less testing but should work)
- [ld64](https://github.com/tpoechtrager/cctools-port), (it needs to be in path as `ld64.ld64`)
- lipo (from cctools-port or llvm-lipo, it needs to be in path as `lipo`)

## Building:

To build for all architectures:

```sh
make release
```

To build for a specific architecture:

```sh
make release ARCHS='x86_64'
```

To build the tests:

```sh
make tests
```

To easily use the library, add the `bin` folder to your path and use the compiler wrappers:

```sh
x86_64-apple-darwin-cc something.c -lc # libc isn't linked by default
```
