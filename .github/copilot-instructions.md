# Copilot instructions for `learning-c`

## Build and run

- Use the repository Makefile for normal builds:
  ```sh
  make
  ```
  This compiles `basic_calculator.c` as C11 with `-Wall -Wextra -Wpedantic` and writes `build/basic_calculator`.
- Run the interactive calculator with:
  ```sh
  make run
  ```
- Run the automated arithmetic tests with:
  ```sh
  make test
  ```
- There is no separate lint target. For a quick non-interactive application smoke test after building:
  ```sh
  printf '8 + 2\nn\n' | ./build/basic_calculator
  ```
- `.vscode/tasks.json` contains a generated GCC task for debugging the active file; it is not the canonical project build configuration.

## Architecture

- `basic_calculator.c` contains the command-line application. `main` owns the interactive loop:
  1. `read_expression` reads and classifies one input line.
  2. `parse_expression` converts the two operands and operator from text.
  3. `calculate` from `calculator.c` performs the operation and returns both a value and `CalcStatus`.
  4. `display_result` maps the calculation status to user-facing output.
  5. `get_choice` controls whether the loop continues.
- `calculator.h` is the shared interface for the calculation result/status types and `calculate()`. `tests/test_calculator.c` tests this module directly without interactive input.
- Input errors are represented separately from calculation errors. `ExpressionInputStatus` covers invalid input, EOF, and stream errors; `CalcStatus` covers successful results, division by zero, integer overflow, and unknown operators.
- Expression parsing uses `fgets` with a fixed 256-byte buffer, `strtol`, whitespace handling, range checks against `INT_MIN`/`INT_MAX`, and explicit rejection of trailing non-whitespace input.
- Arithmetic is integer arithmetic. `calculate` checks overflow before `+`, `-`, and `*`, handles the `INT_MIN / -1` case explicitly, and rejects division by zero.

## Repository conventions

- Keep the code portable C11 and preserve clean builds under `-Wall -Wextra -Wpedantic`.
- Prefer the existing status/result pattern when adding behavior: return a typed status alongside computed data rather than printing errors from parsing or arithmetic helpers.
- Keep input acquisition, parsing, calculation, and presentation separate. New validation belongs near parsing; operation-specific safety checks belong in `calculate`; user-facing messages belong in `display_result` or the surrounding interactive loop.
- Preserve the current input behavior: accept surrounding whitespace, require exactly one operator followed by a valid integer, reject overlong lines and trailing non-whitespace, and distinguish EOF/read errors from ordinary invalid input.
- Use the Makefile’s `build` output path for generated binaries. Do not add generated executables or debugger artifacts to source control; `/build/` is ignored.
