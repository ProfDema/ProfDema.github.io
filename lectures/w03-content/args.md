### Command-Line Arguments: Key Points

`./mycalc add 5 4 3 2 1`

1. Just like `stdin`, command-line arguments are another
method of providing *input* to a program.
2. Use `strtol()` to parse strings containing integers
  * More robust than other methods
  * We don't want segmentation faults when processing
  invalid input: Always terminate gracefully upon errors

---

## Command-Line Arguments Worksheet

