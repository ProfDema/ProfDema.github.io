## Extra Slides 

---

### Limitations of Select

* `select()` has some performance limitations, and can only monitor
at most `FD_SETSIZE` (1024, on Linux) file descriptors
* But it is portable and simple to use

---

### SIGPIPE

Writing to a broken pipe/socket generates a `SIGPIPE`.

Recall: By default, most signals will terminate your program.

Assignment 4 adds:

```c
/* 
 * Turn off SIGPIPE: write() to a socket that is closed on the other
 * end will return -1 with errno set to EPIPE, instead of generating
 * a SIGPIPE signal that terminates the process.
 */
if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
    exit(1);
}
```
<!-- .element class="stretch" -->

---

### Non-Blocking Reads

* You can change the behaviour of `read()` so that it returns `-1`
and sets `errno` to `EAGAIN` if no data is available.
* In this mode, `read()` will never block
* Downside: Leads to inefficient code, e.g., using an infinite loop
that repeatedly calls `read()`
  * Remember, `read()` will return **immediately** in non-blocking mode,
  so you will be calling it **many** times per second

---

### Non-Blocking Reads: Sample Code

```c
char buf[1024];
ssize_t bytesread;
/* set O_NONBLOCK flags on fd1 and fd2 */
if (fcntl(fd1, F_SETFL, O_NONBLOCK) == -1) {
  perror("fcntl"); exit(1);
}
if (fcntl(fd2, F_SETFL, O_NONBLOCK) == -1) {
  perror("fcntl"); exit(1);
}
   
for ( ; ; ) {
  bytesread = read(fd1, buf, sizeof(buf));
  if ((bytesread == -1) && (errno != EAGAIN))
    return;    /* real error */
  else if (bytesread > 0)
    doSomething(buf, bytesread);         
  bytesread = read(fd2, buf, sizeof(buf));
  if ((bytesread == -1) && (errno != EAGAIN))
    return;    /* real error*/
  else if (bytesread > 0)
    doSomething(buf, bytesread);
}
```
