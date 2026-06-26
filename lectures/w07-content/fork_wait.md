### Processes

* A *process* is an instance of an executing *program*
* Executing multiple instances of the same program
launches multiple processes
  * e.g., run multiple instances of Notepad
* A single program may launch multiple processes
  * Firefox/Chrome run one-process-per-tab
  * Assignment 3

---

### Process Memory

<div class="container">
<div class="col" style="max-width:50%; margin: auto auto; vertical-align: center;">

Each process has its own memory space, including its own stack and heap.

A process cannot access the variables/memory
of another process.

</div>

<div class="col" style="max-width:50%; margin: auto auto; vertical-align: center;">

![](./w07-figs/memory_model.svg)
<!-- .element class="stretch" -->

</div>
</div>

---

### Process Creation

* In UNIX-like systems, processes are created with
the `fork()` system call
* The process that calls `fork()` is the *parent* of the
newly-created *child* process
* Try `pstree` from a Bash shell to print the tree
of currently-running processes

---

### Process Identifiers

* Each process has a PID (process identifier)
* The first process created when the system boots up
is the `init` process, with PID 1
  * On Ubuntu, the `init` process is `systemd`
  * On macOS, the `init` process is `launchd`

---

### Program Exit Status vs. Process Exit Status

Every program reports an *exit status* upon completion/termination.
This is done via `exit()`.

`void exit (int status)`

Here, `status` is the *program's exit status*, which becomes **part** of the *process' termination status*.

[Source: The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Normal-Termination.html#Normal-Termination)

---

### Obtaining the Exit Status

![](./w07-figs/exitstatus.svg)

> A *process exit status* is saved to be reported back to the parent
> process via `wait` or `waitpid`. If the program exited, this
> status includes as its low-order 8 bits the *program exit status*.

[Source: The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Termination-Internals.html)

---

### Exit vs. Return

Inside `main()`, `return` and `exit()` are nearly equivalent (save some edge cases):

1. The return value of `main()` is the *program exit status* passed to `exit()`.
2. `exit()` performs some cleanup (e.g., flush `stdio` streams) and calls `_exit()`.
3. `_exit()` sets the *process exit status*, or *termination status*, and terminates the process.

Outside of `main()`, use `exit()` to terminate the process.

---

Try:
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Hi");
    exit(0); // equivalent to "return 0;"
}
```

vs.

```c
#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Hi");
    _exit(0);
}
```

What's the difference?

---

### Exit Status Conventions

Return `0` on success, any other value on error.

[But if you're a real GNU/Linux geek...](https://www.gnu.org/software/libc/manual/html_node/Exit-Status.html)

> A general convention reserves status values 128 and up for
> special purposes. In particular, the value 128 is used to
> indicate failure to execute another program in a subprocess.

---

### Question
How do we obtain the program exit status from the process exit status?

### Answer
Use macros defined in `wait.h` (see `man 2 wait`), e.g.,
* `WIFEXITED(status)` to see if process terminated normally or abnormally
* `WEXITSTATUS(status)` to obtain program exit status

---

### Question
What happens if a process terminates before its parent obtains
its exit status?

### Answer
The child process becomes a *zombie process*.

Operating system retains minimal information about the process
until the parent obtains exit status via `wait()`.

---

### Question
What happens if a parent process terminates before waiting
for all its children?

### Answer
The child processes become *orphan processes*.

Orphan processes are *adopted* by the `init` process.

---

Which statements are true when `fork()` is called?

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/fork"></iframe>

---

## Fork and Wait Worksheet

---

### File Descriptors

The `FILE` structure used by `stdio` functions (e.g., `fopen`)
includes an integer called a *file descriptor*.

The OS maintains a per-process *file descriptor table*.

A child process gets a **copy** of the parent's file descriptor table.

So all open files open in the parent **before** the `fork` are
also open in the child.

File descriptors in different processes may refer to the same
*open file description* in OS's *open file table*.

Note:
Immediately after the `fork`, both parent and child's file descriptors
refer to the same *open file descriptions*
in the system-wide *open file table*.

---

### File Descriptors vs. File Descriptions

![Mapping between file descriptors and file descriptions](./w07-figs/file_descriptors.svg) <!-- .element width="70%" -->

---

### Sharing the Same Open File Description

If the parent process `open`s a file before a `fork`:
* Whichever process (parent or child) calls `fread` first
will read the first `N` bytes
* Whichever process calls `fread` afterwards will read
the next `M` bytes

Since both parent and child processes refer
to the same file description, they both share the
same *offset* value.

---

### Inter-Process Communication

Exit statuses provide a very limited form of *inter-process communication*,
specifically between a child and parent process.

Next week we will discuss *pipes*, which are a more useful mechanism
for communicating between processes.

Open pipes are also associated with file descriptors,
so they can be read/written very similarly to regular files.
