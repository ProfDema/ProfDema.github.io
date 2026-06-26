### The exec Functions

The `exec` functions *load a new program* into the current process image.
The process retains its original PID.

The functions differ mainly in how they are called, e.g.,

```c
char* args[] = {"ls", NULL};
execve("/bin/ls", args, NULL);
```

vs.

```c
execle("/bin/ls", "ls", NULL, NULL);
```

---

![Comparison of exec functions](./w07-figs/exec_comparison.svg) <!-- .element width="100%" -->

Also: `execve()` is a system call; the others are C standard library functions

---

### Exec and the Shell

A shell can use `fork` and `exec` to execute other programs:

1. Shell process `p` waits for keyboard input.
2. You type `ls`.
3. Shell forks child proces `c`.
4. Process `c` uses an `exec` function to run `ls`.
5. Process `p` calls `wait` to wait for `c` to terminate, and then prints new prompt.

---

### Exec and File Descriptors

When a program calls `exec`, the new program still retains
the file descriptors of the original process.

But the `FILE *` variables are gone,
upon replacing the process image with the new program.

So the new program must either:
1. Perform low-level I/O using the `read()` or `write()`
system calls (you will do this with *pipes* on Assignment 3); or
2. Use `fdopen()` to associate a new buffered file stream
with an existing open file descriptor.
