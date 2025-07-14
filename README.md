# Customisable Programming Language Compiler

This repository contains a minimal example of a compiler for a very
small, customisable programming language. The code is written in C++ and
uses a simple lexer, parser and bytecode interpreter. It demonstrates
how a custom language can be compiled and executed on both Linux and
Windows using standard build tools.

## Features

- Variable declarations using `let`
- Integer arithmetic with `+`, `-`, `*`, `/`
- Print statements
- Cross platform build via CMake

The implementation is intentionally small but can be extended with more
language features such as conditionals, loops or additional data types.

## Building

### Linux
```bash
mkdir build
cd build
cmake ..
make
```

### Windows (with CMake and a compiler like MSVC or MinGW)
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"   # choose a generator available on your system
cmake --build .
```

After building, the executable `cplc` (or `cplc.exe` on Windows) can be
used to compile and run `.cpl` source files.

## Usage
Create a file `example.cpl` with the following contents:
```text
let x = 10;
let y = x * 2 + 5;
print y;
```
Run the compiler:
```bash
./cplc example.cpl
```
The program will print `25`.

## Hardware Adaptation
The current implementation compiles natively for the host CPU using the
system compiler. No architecture-specific optimisation is performed yet.
Further work could add more advanced optimisations and native code
generation.

## Questions
- Which advanced language features would you like to see added?
- Should the compiler eventually emit native code instead of running in
a virtual machine?
