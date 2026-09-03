# Simpletron

Simpletron is a small C++ implementation of the classic Simpletron machine language (SML) virtual machine. It loads a program from a text file, executes it in memory, and supports input/output, arithmetic, branching, and halting instructions.

## What this project includes

- A Simpletron runtime implemented in C++
- A command-line entry point for running SML programs
- A test suite using GoogleTest
- Example SML programs in the `sml/` directory

## Project layout

- `src/` — implementation and runtime code
- `src/include/` — public headers
- `sml/` — sample Simpletron programs
- `test/` — automated tests
- `CMakeLists.txt` — project configuration

## Requirements

- CMake 3.20 or newer
- A modern C++ compiler with C++20 support

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

This produces the executable under `build/src/`.

## Run a program

```bash
./build/src/simpletron-app sml/two_num_sum.sml
```

If no file is provided, the app falls back to `input.sml` in the current working directory.

## Example SML program

```text
+1007
+1008
+2007
+3008
+2109
+1109
+4300
+0000
+0000
+0000
```

This example reads two numbers, adds them, stores the result, and halts.

## Supported operations

- `READ` (`10`) — read a value into a memory location
- `WRITE` (`11`) — write a value from memory to output
- `LOAD` (`20`) — load a value into the accumulator
- `STORE` (`21`) — store the accumulator into memory
- `ADD` (`30`) — add a value to the accumulator
- `SUBTRACT` (`31`) — subtract a value from the accumulator
- `DIVIDE` (`32`) — divide the accumulator by a memory value
- `MULTIPLY` (`33`) — multiply the accumulator by a memory value
- `BRANCH` (`40`) — branch to an address
- `BRANCHNEG` (`41`) — branch if accumulator is negative
- `BRANCHZERO` (`42`) — branch if accumulator is zero
- `HALT` (`43`) — terminate execution

## Run tests

```bash
ctest --test-dir build/test --output-on-failure
```

## Notes

The project is intentionally small and educational, making it a good reference for learning simple virtual machines and instruction-set design.
