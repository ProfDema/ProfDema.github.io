### Reading From Multiple File Descriptors

Assume that a process `p0` has any two file descriptors open
for reading (e.g., from a socket, regular file, pipe)

![](./w11-figs/two_fds.svg)

---

### Reading From Multiple File Descriptors (2)

If `p0` reads from `fdN`, it will block until `fdN` has
data ready to read. But what if the other file already has
data available to be read?

![](./w11-figs/two_fds.svg)

---

### Solution 1: Fork

`p0` can `fork` one child process per file descriptor to be read from;
each child calls `read` on one file descriptor and communicates data
to parent over a pipe.

![](./w11-figs/two_fds_two_processes.svg)

Which should be called first: `read()` or `wait()`?

---

### Solution 1: Fork (With Sockets)

* It is common for server software to `fork()` a new process for
each client that connects: SSH does exactly that
* *Performance* benefit: Solves the issue of blocking `read()` calls that
we just discussed
* *Security* benefit: Each process has its own memory space, making it
less likely for there to be a bug that allows one user to read
confidential information that belongs to another user
* Drawback: Each process takes up memory

---

### Solution 2: Select

* `select()` monitors several file descriptors
simultaneously, without needing to `fork()`
* `select()` **blocks** until at least one of the monitored
file descriptors is "ready"
* A file descriptor "ready" for reading means that
`read()` can be called **once** without blocking
  * Calling `read()` more than once can block
* `select()` also returns on some other conditions, e.g.,
if a signal is received,
or a predefined timeout period expires

---

### Select: Parameters

* `select()` takes three file descriptor sets as input:
  * First set is monitored for *reading*
  * Second set is monitored for *writing*
  * Third set is monitored for *exceptions*
  
For the keen:
[An example of what would trigger an exception](https://www.gnu.org/software/libc/manual/html_node/Out_002dof_002dBand-Data.html)

---

### Select and the Listener Socket

* Recall that `accept()` is a blocking call that returns after
a new incoming connection is added to the listener socket's queue
* The listener socket file descriptor can be monitored with
`select()`: It is considered "ready to read" when there is at least
one connection queued up to be accepted

---

### File Descriptor Sets

File descriptor sets are similar to signal sets. Use following
macros to operate on them:

1. `FD_ZERO()`: Empty the set
2. `FD_SET()`: Add file descriptor to the set
3. `FD_CLR()`: Remove file descriptor from the set
4. `FD_ISSET()`: Check file descriptor's membership in a set

---

### Select: The Bottom Line

* The bottom line is that we **never** want to block on any calls to
`read()` or `accept()`
  * Otherwise, we risk the possibility of waiting forever,
  even when there might be data ready to be read from other
  file descriptors
* Instead, we write our client/server programs to block **only**
on `select()`

---

### Assignment 4 Debugging Tip

Use the `strace` utility on your client and/or server: If it ever
blocks on `read()` or `accept()`, it means there is a bug in your
program

---

### Question

Our Assignment 4 server is written to not block on any `read()`
calls, but what if it blocks on `write()`?

### Answer

We've only scratched the surface with this course. When might a server
block on `write()`? Hint: See "extra slide" on flow control from
last week. What does TCP do if a server is sending data faster
than a client can handle?

Solution: Use `select()` for both reads and writes.

---

### Select Worksheet
