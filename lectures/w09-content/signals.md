### Signals

* Signals are unexpected, asynchronous events that can happen at any time
* Unless you make special arrangements, most signals terminate your process

---

### Signals You Already Know

* Signals are another basic form of Inter-Process Communication
* You have already been sending signals through the shell, e.g.,
via the `ctrl+c` and `ctrl+z` key combinations

---

### Question

When you hit `ctrl+c` to terminate a program, what really happens?

### Answer

The terminal sends the `SIGINT` signal to the process.

By default, `SIGINT` ("Interrupt from keyboard") terminates the process.

Similarly, `ctrl+z` triggers a `SIGSTP` signal ("Stop typed at terminal")

---

### Other Signals

The kernel sends several other signals to terminate processes when
a program misbehaves:

* `SIGSEGV` Invalid memory reference
* `SIGFPE` Floating-point exception
* `SIGILL` Illegal instruction

There are also the user-defined signals `SIGUSR1` and `SIGUSR2`,
that we can use for our own purposes. By default they terminate the process.

---

### Sending Signals From The Shell

To send a signal `SIGNAME` to one or more processes:

`$ kill -SIGNAME pid`

For example:

`$ kill -SIGINT 11248`

`$ kill -SIGKILL 11248`

The `SIGKILL` and `SIGSTOP` signals cannot be caught, blocked, or ignored
(see `man 7 signal`).

---

### Signal Handling

There are three options for handling signals:

1. Write a signal handler function, which will be called automatically upon
receipt of a signal.
2. Ignore the signal (i.e., the signal does nothing to your process).
3. Use the default action.

---

### Changing the Default Action

Two options for changing the default signal action:
1. The `sigaction()` system call
2. The `signal()` C standard library function

`signal()` is cross-platform but more limited in scope,
whereas `sigaction()` is more flexible but found only on
POSIX.1-compliant systems.

[More in the GNU C library manual](https://www.gnu.org/software/libc/manual/html_node/Signal-and-Sigaction.html)

---

### Protip

`sigaction` is both the name of the system call,
and the struct that it takes as the 2nd and 3rd arguments:

```
int sigaction(int sig,
    const struct sigaction *act,
    struct sigaction *oldact);
```

---

### What is a Signal Action?

```
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int      sa_flags;
    void     (*sa_restorer)(void);
};
```

`sa_handler` can be set to `SIG_IGN` (ignore), `SIG_DFL` (default action),
or the address of a handler function (see `man 2 sigaction`).

---

```c
/* EXAMPLE */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int i = 0;

void handler(int signo) {
  fprintf(stderr, "Sig %d; total %d.\n", signo, ++i);
}

int main(void) {
  struct sigaction newact;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  newact.sa_handler = handler;
  if (sigaction(SIGINT, &newact, NULL) == -1) exit(1);
  if (sigaction(SIGTSTP, &newact, NULL) == -1) exit(1);

  for(;;); //Infinite loop
}
```

---

### Sending A Signal From One Process to Another

One process can send a signal to another process using the
misleadingly-named `kill()` system call.

---

### Signal Sets

A signal set (`sigset_t`) is a *bit vector* that specifies the set of
signals to block; operate on them using the following standard library functions:

1. `int sigemptyset(sigset_t *set);`
2. `int sigfillset(sigset_t *set);`
3. `int sigaddset(sigset_t *set, int signo);`
4. `int sigdelset(sigset_t *set, int signo);`
5. `int sigismember(const sigset_t *set, int signo);`

See `man 3 sigsetops` for usage.

Note:
Also recall last week's discussion on bitwise operators.

---

### Masking Signals During Program Execution

* As our program may receive signals spontaneously at any time, we may
need to block some signals from being delivered at an inopportune
moment (e.g., writing to disk).
* This *temporary* block is different from ignoring a signal entirely.
* Use the `sigprocmask()` system call to examine or change the set of blocked
signals, via a *mask* (i.e., a bit vector representing a set of signals)

---

### Masking Signals During Signal Handler Execution

From `man 2 sigaction`:

> sa_mask specifies a mask of signals which should be blocked (i.e.,
> added to the signal mask of the thread in which the signal handler is
> invoked) during execution of the signal handler.  In addition, the
> signal which triggered the handler will be blocked, unless the
> SA_NODEFER flag is used.

---

### Types and Portability

What is a `sigset_t` anyway?
Good opportunity to demonstrate the primary need for `typedef`: Allowing
us to write *portable code*

From `x86_64-linux-gnu/bits/types/sigset_t.h`:

```c
typedef __sigset_t sigset_t;`
```

From `x86_64-linux-gnu/bits/types/__sigset_t.h`:

```c
#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct
{
    unsigned long int __val[_SIGSET_NWORDS];
} __sigset_t;
```

---

### Masking Signals: Example

```
sigset_t set, oldset;
sigemptyset(&set);
sigaddset(&set, SIGINT);
sigprocmask(SIG_BLOCK, &set, &oldset);
/*... Critical operation ...*/
sigprocmask(SIG_SETMASK, &oldset, NULL);
```

---

### Pending Signals

* A blocked signal will be delivered if it is later unblocked
* Between the time when it is generated and when it is delivered,
a signal is said to be *pending* (see `man 7 signal`)
* The `sigpending` system call allows you to examine the
currently-pending signals

---

### Writing to a Broken Pipe

* `SIGPIPE` is sent to a process that tries to write to a pipe
or to a *socket* that does not have any readers

---

### Limitations of Signals: Information

* Signals convey no information, aside from what type of signal
(e.g., `SIGINT`, `SIGUSR1`) it is
* Generally only used to indicate abnormal conditions: Not
for data exchange

---

### Limitations of Signals: Queuing
* Multiple instances of the same signal do not queue
* If signal `X` is sent while a previously-sent signal `X` is pending,
then the second `X` is lost
* Example, if your process receives a `SIGCHLD` (Child stopped
or terminated), it may be that only one child process has terminated,
or that *multiple* child processes have terminated

---

### Signal Safety

* An *async-signal-safe* function is one that can be safely called from
within a signal handler.

**None of the `stdio` functions are async-signal-safe.**

* Yes: If we give you any examples that use `stdio` functions in a signal
handler, the examples may not always run properly
* A safe technique is to set *global variable* flags from the signal
handler and call the `stdio` functions from your "main" program code

---

### Async Signal Safety

From `man 7 signal-safety`:

> Suppose a program is in the middle of a call to a `stdio`
> function such as `printf` where the buffer and associated variables have
> been partially updated. If, at that moment, the program is interrupted
> by a signal handler that also calls `printf`, the second call to
> `printf` will operate on inconsistent data, with unpredictable results.

---

### Exercise

Select the statements that are true.

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/signals"></iframe>

---

## Signals Worksheet
