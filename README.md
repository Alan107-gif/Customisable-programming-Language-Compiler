# Customisable Programming Language Compiler

This project contains a comfortable yet small compiler for a toy programming language. It demonstrates how to build and run a custom language on Linux and Windows.

## 1. Installing and Using

### Building

#### Linux
```bash
mkdir build
cd build
cmake ..
make
```

#### Windows
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"  # or another generator
cmake --build .
```

The build will produce an executable `cplc` (or `cplc.exe` on Windows). You can rename the file to any extension such as `.x` or `.xxx` to suit your workflow – on Linux any executable name will run.

### Running
Create a file `example.cpl`:
```text
let x = 10;
let y = x * 2;
print y;
```
Run:
```bash
./cplc example.cpl
```
The program prints `20`.

## 2. Practical Work and Customisation

The language now supports variable declarations, assignments, arithmetic, comparison operators, `if`/`else`, `while` loops and user defined functions. A function is declared with `fn`:

```text
fn add(a, b) {
    return a + b;
}

let result = add(2, 3);
print result;
```

All language features are implemented in `lexer.cpp`, `parser.cpp` and `vm.cpp`. You can further extend them to add Python-like data types such as lists.

To modify the language:
1. Edit **lexer.cpp** to recognise new keywords or symbols.
2. Update **parser.cpp** to emit bytecode for new constructs.
3. Implement behaviour in **vm.cpp**.

Because the compiler produces standard native executables via CMake, you may tune compilation flags or rename the resulting binary to match any extension. Further work could add optimisation passes and native code generation.

Questions for future work:
- Which additional high level features (functions, lists, etc.) would be most useful?
- Would integrating a just-in-time backend improve performance?
