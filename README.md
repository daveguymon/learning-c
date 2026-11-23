```text
  .-----------.
  |  _______  |
  | | 0.00  | |
  | |_______| |
  | 7 | 8 | 9 |
  |---+---+---|
  | 4 | 5 | 6 |
  |---+---+---|
  | 1 | 2 | 3 |
  |---+---+---|
  | 0 | . | = |
  '-----------'
```

# learning-c

A simple C expression calculator for signed integers.

## Calculator behavior

Enter an expression in this format:

```text
first number operator second number
```

For example:

```text
8 + 2
```

The calculator supports these operators:

| Operator | Operation |
| --- | --- |
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Integer division |

Surrounding whitespace is allowed. Operands must be signed decimal integers
within the range of the C `int` type. Successful calculations print the result:

```text
Result: 10
```

The calculator reports these conditions:

- `Invalid input.` means the expression is missing an operand or operator,
  contains an out-of-range number, has trailing non-whitespace text, or is too
  long.
- `Error: Division by zero.` means `/` was used with a zero second operand.
- `Error: Integer overflow.` means the result is outside the `int` range.
- `Error: Unknown operator '...'.` means the expression used an operator other
  than `+`, `-`, `*`, or `/`.

After a calculation, enter `y` to continue or `n` to exit. Invalid choices are
rejected until `y` or `n` is entered.

### Example session

```text
$ ./build/basic_calculator
Enter an expression (for example, 8 + 2): 8 +
Invalid input.
Enter an expression (for example, 8 + 2): 8 + 2
Result: 10
Do you want to continue? (y/n): n
```

## Build, run, test, and clean

Build the calculator with the default C compiler and warning flags:

```sh
make
```

This creates `build/basic_calculator`. Build and run the interactive calculator
with:

```sh
make run
```

The default build uses C11 with `-Wall -Wextra -Wpedantic`.

Run the automated arithmetic tests with:

```sh
make test
```

Remove generated binaries and object files with:

```sh
make clean
```
