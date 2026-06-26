### Pipes

* A *pipe* is a one-way, first-in first-out (FIFO) communication
channel that can be used between two processes
* Pipes are created using the `pipe()` system call
* A pipe has two file descriptors: One for reading and one for writing
* For usage: `man 2 pipe`
* For useful background info: `man 7 pipe`

---

### Using a Pipe in a Single Process

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 13
char *msg = "hello, world\n";

int main(void)
{
  char buf[MSG_SIZE];
  int p[2];
  if (pipe(p) == -1) {
    perror("pipe");
    exit(1); 
  }
  write(p[1], msg, MSG_SIZE); // No error checking: Bad
  read(p[0], buf, MSG_SIZE); // No error checking: Bad
  write(STDOUT_FILENO, buf, MSG_SIZE);
  return 0;
}
```

---

### Pipe for Inter-Process Communication

* Recall: Upon calling `fork()`, child process gets a copy of the
parent process' file descriptor table
* So if a process creates a pipe, and then forks, the child process
will have a copy of the file descriptors to the pipe
* This allows the parent and child to communicate across the pipe

---

### Child Communicating to Parent Over a Pipe

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 13
char *msg = "hello, world\n";
int main(void) 
{
  char buf[MSG_SIZE];
  int p[2];
  if (pipe(p) == -1) {
    perror("pipe");
    exit(1);
  }
  if (fork() == 0) //Child writes
    write(p[1], msg, MSG_SIZE); // No error checking: Bad
  else { //Parent reads from pipe and prints
    read(p[0], buf, MSG_SIZE); // No error checking: Bad
    write(STDOUT_FILENO, buf, MSG_SIZE); // No error checking: Bad
  }
  return 0;
}
```

---

### Closing Unneeded File Descriptors

* Each process should close any file descriptors that it is not
using: Especially with pipes
* If a process calls `read()` on a pipe, but there is no data
ready to be read, it will **stall forever**, unless:
  * New data arrives on the pipe; or
  * **All** file descriptors (across all processes) referring to
  the write end of the pipe have been closed
* Again: Read and understand `man 7 pipe`
* If your Assignment 3 code stalls, try running it under `strace -f`
to see if it is stalling on a `read()` call

---

## Pipes Worksheet

---

## Extra Slides

---

### More on Pipes

From `man 7 pipe`, under *I/O on pipes and FIFOs*:

1. Pipes have no message boundaries. If you `write` to a pipe twice
and then `read` from it, don't assume that you will just
receive the first chunk of data that you wrote.
2. `write` is guaranteed to be *atomic* only if the data being
written is smaller than a certain number of bytes (on Linux, 4KB).

---

### More on Pipes (2)

From `man 7 pipe`, under *Pipe capacity* heading:

3. Pipes have a finite size: Default is 64KB on Linux.
4. If a `write` would overflow a pipe, the process blocks
(or fails, if `O_NONBLOCK` flag is used when creating the
pipe) until another process
empties some of the data from the pipe by calling `read`.
