### Low-Level I/O

When we want to do low-level I/O, to bypass the buffering and
abstractions provided by the C standard library, we must
use *system calls*, namely:
  * `open()`
  * `close()`
  * `read()`
  * `write()`

Many different flags, errors, corner cases, etc. to consider:
See `man 2 XXX`, where `XXX` is the name of the system call.

---

Repeated for emphasis: Proper usage of low-level I/O often requires
looping and handling error conditions.

```c
ssize_t ret;
while (len != 0 && (ret = read(fd, buf, len)) != 0) {
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

### Low-Level I/O and File Descriptors

* Low-level I/O is done using *file descriptors*, which are integer
values that serve as indices for open files
* Each process has its own *file descriptor table*
  * File descriptor `N` in *process A* can refer to a different file
  from file descriptor `N` in *process B*

---

### File Descriptors vs. File Descriptions

![Mapping between file descriptors and file descriptions](./w07-figs/file_descriptors.svg) <!-- .element width="70%" -->

---

### Exec and File Descriptors

When a program calls `exec`, the new program still retains
the file descriptors of the original process.

But the `FILE *` variables are gone,
upon replacing the process image with the new program.

So the new program must either:
1. Perform low-level I/O using the `read()` or `write()`
system calls; or
2. Use `fdopen()` to associate a new buffered file stream
with an existing open file descriptor.

---

### dup and dup2

`int dup(int oldfd)`

`int dup2(int oldfd, int newfd)`

* `dup` returns a new FD that refers to same file as `oldfd`
* `dup2` does the same, but lets you specify value of new FD
  * `dup2` first closes `newfd` if already in use

---

### Output Redirection with dup2

```
int main (void)
{
    int fd = open("lsout", O_WRONLY | O_CREAT, 0600);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO) ;
    execl("/bin/ls", "ls", "-l", (char *)NULL);
    perror("execl");
    return 1;
}
```
