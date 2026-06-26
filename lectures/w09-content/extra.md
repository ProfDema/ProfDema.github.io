## Extra Slides

---

### Efficiently Pausing a Program

Using an empty loop is a very inefficient wa yto await the arrival of
a signal. This is like running in place rather than sitting down.
We may instead use the `pause` system call
to suspend execution until a handled signal
arrives.

Caution: `pause` can result in "missing" a signal.

---

### Efficiently Pausing a Program: Example

In the following example, we write a program that:

1. Blocks `SIGINT` while doing some important work
2. Unblocks `SIGINT`
3. Waits for a `SIGINT` to be sent
before terminating

Any `SIGINT` sent during the important work should "count"
(i.e., terminate the program after `SIGINT` is unblocked)

Note that signals can still sneak in after the unblock
and before the `pause`.

---

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void handler(int signo) {
  fprintf(stderr, "Caught!\n");
}

int main(void) {
  time_t startTime;
  sigset_t mask, oldmask;
  struct sigaction newact;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  if (sigprocmask(SIG_BLOCK, &mask, &oldmask) == -1)
    exit(1);
  sigemptyset(&newact.sa_mask); newact.sa_flags = 0;
  newact.sa_handler = handler;
  if (sigaction(SIGINT, &newact, NULL) == -1)
    exit(1);

  fprintf(stderr, "SIGINT blocked. Doing important work\n");
  startTime = time(NULL);
  while (time(NULL) < startTime + 10);

  fprintf(stderr, "Now unblocking SIGINT\n");
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1)
    exit(1);
  pause();
  fprintf(stderr, "Got the SIGINT. Exiting...\n");
  return 0;
}
```

---

### More on Typedefs

[The Linux kernel coding style](https://www.kernel.org/doc/html/latest/process/coding-style.html#typedefs)
should help further clarify the purpose of `typdef`s
such as `sigset_t` that are used in the Linux system call
interfaces.

In short: To present an abstraction for types that
should only be accessed/manipulated using a specific set of
functions (e.g., like how a `sigset_t` should only be modified/accessed
via the `sigsetops` functions).
