### System Calls vs. Library Calls

* System calls are the interface by which programs request
services from the operating system kernel
* Standard C library functions (e.g., string library functions)
are **not** system calls
  * Some serve as "wrappers" around system calls (e.g.,
  `fopen()` calls `open()`)

---

### System Calls and Portability
* Usage of C standard library functions is *portable*
  * But need to recompile on different platforms
* Usage of system calls is **not** portable, unless you
  * Use (e.g., POSIX-compliant) system calls
  supported by multiple operating systems
  (see `COMFORMING TO` heading in system call man pages)
  * Write separate implementations of OS-dependent code,
  compile multiple platform-specific executables (using
  C preprocessor macros)

---

### Error-Checking

* All system calls and some library functions use `errno` to
return error values
  * See `man errno` for complete list of error names defined
  in `errno.h`

---

Q: How many systems programmers does it take to change a light bulb?

A: Just one, but they will keep changing it until it returns 0.

---

Simplistic use of system calls is not suitable for proper
error handling. Example below demonstrates proper usage of `read()` to
read `len` bytes.

```c
ssize_t ret;
while (len != 0 && (ret = read (fd, buf, len)) != 0) {
    if (ret == −1) {
        if (errno == EINTR)
            continue;
        perror ("read");
        break;
    }
    len -= ret;
    buf += ret;
}
```

---

## Errors Worksheet
