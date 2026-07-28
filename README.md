# Forth Interpreter

[![Language: C](https://img.shields.io/badge/language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status: Experimental](https://img.shields.io/badge/status-experimental-orange.svg)](#project-status)

A lightweight, educational Forth-style interpreter written in C. The project provides an interactive, stack-based environment with arithmetic, stack manipulation, user-defined words, conditional execution, loops, and basic terminal output.

> [!NOTE]
> This project implements a practical subset of Forth for learning and experimentation. It is not currently a complete ANS Forth implementation.

## Features

- Interactive read-evaluate-print loop (REPL)
- Floating-point data stack
- User-defined words with `:` and `;`
- Conditional execution with `if`, `else`, and `then`
- Counted loops with `do`, `i`, and `loop`
- Numeric, comparison, bitwise, and output operations
- Cross-platform Makefile targets for Windows and Unix-like systems

## Supported Words

| Category | Words |
| --- | --- |
| Arithmetic | `+`, `-`, `*`, `/`, `mod` |
| Stack manipulation | `dup`, `drop`, `swap`, `over`, `rot` |
| Comparison | `=`, `<`, `>` |
| Bitwise | `and`, `or`, `invert` |
| Output | `.`, `emit`, `cr`, `."` |
| Control flow | `if`, `else`, `then`, `do`, `i`, `loop` |
| Definitions | `:`, `;` |
| Session | `exit` |

## Requirements

- A C11-compatible compiler such as [GCC](https://gcc.gnu.org/)
- `make`

## Build

Clone the repository and compile the interpreter:

```bash
git clone https://github.com/itsmustafa119/Forth-Interpreter.git
cd Forth-Interpreter
make
```

Run it with:

```bash
make run
```

You can also launch the compiled executable directly:

```bash
./main
```

On Windows:

```powershell
.\main.exe
```

To remove the compiled executable:

```bash
make clean
```

## Usage

The interpreter displays the current stack before reading each line. Enter numbers and words separated by spaces.

### Arithmetic

```forth
2 3 + .
10 4 - .
6 7 * .
20 5 / .
```

### Stack operations

```forth
10 dup
10 20 swap
1 2 over
1 2 3 rot
```

### Define a word

```forth
: square dup * ;
5 square .
```

### Conditional execution

```forth
5 3 > if 1 . else 0 . then
```

### Counted loop

```forth
10 0 do i . loop
```

### Character output

```forth
65 emit
```

Enter `exit` to close the interpreter.

## How It Works

1. The REPL reads a line and splits it into space-delimited tokens.
2. Numeric tokens are pushed onto the data stack.
3. Built-in words operate on the stack or control evaluation.
4. User-defined words are stored in an in-memory dictionary and expanded when invoked.
5. The interpreter prints command output and waits for the next line.

## Project Structure

```text
.
|-- main.c       # Interpreter, stack, dictionary, and REPL
|-- Makefile     # Build, run, and clean targets
`-- .gitignore   # Generated and editor-specific files
```

## Project Status

Forth Interpreter is an experimental learning project. It is suitable for exploring stack-based language implementation, but it should not yet be treated as a production-ready or standards-compliant Forth environment.

## Contributing

Contributions are welcome:

1. Fork the repository.
2. Create a focused feature or fix branch.
3. Keep changes small and clearly documented.
4. Test the affected interpreter behavior.
5. Open a pull request describing the change and its motivation.

When reporting a bug, include the input sequence, expected result, actual result, compiler, and operating system.

## License

No license has been selected for this project yet. Until a license file is added, the repository remains under the copyright terms that apply by default.
