## Extras

---

### Reading Address Sanitizer Output

Examples from the discussion board:
1. [Unsafe WRITE](https://mcsapps.utm.utoronto.ca/forum/t/heap-buffer-overflow/4495/3?u=alacafur)
2. [Unsafe READ](https://mcsapps.utm.utoronto.ca/forum/t/assignment-1-error-help/4461/11)

[Complete list of memory errors that Address Sanitizer can detect](https://github.com/google/sanitizers/wiki/AddressSanitizer)

---

### Challenge (New tool, for those interested)

Can your Assignment 1 handle any input without segfaulting?
Try testing with [American Fuzzy Lop](https://github.com/google/AFL)

```bash
$ sudo apt install afl
$ afl-gcc -Wall -Werror -o effects effects.c
$ AFL_SKIP_CPUFREQ=TRUE afl-fuzz -i samples/ -o findings/ ./effects -fin 100
```

`samples`: Directory containing valid input files created with `xxd -g1 X.wav`; ideally <100KB for performance

`findings`: Directory for storing test results

Don't use Address Sanitizer and AFL together (too much RAM)
