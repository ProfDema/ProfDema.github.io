### Pointers Recap From Last Week

1. `*` and `&` are *operators*
  * `&` "returns" the address of any *named* variable
  * `*` dereferences any *address* (whether stored in a pointer or not)
2. **Only** for variable declaration, `*` serves to **identify** 
variables that are pointers
3. When reading/writing a pointer variable without dereferencing,
you are reading/writing the **addresss** contained in the pointer

---

### Casting Pointers

What does the following program print:

```c
#include <stdio.h>
int main() {
       int x = 0x00616263;
       char *y = (char *)&x;
       printf("%s", y);
       return 0;
}
```

* Hint: See [ASCII Table](http://www.asciitable.com/)
* Notice the ordering of the bytes
* You are expected to understand hexadecimal:
[Read this forum post to clear up any confusion][hex_post]

[hex_post]: https://mcsapps.utm.utoronto.ca/forum/t/required-reading-1000-words-everything-you-need-to-know-about-hexadecimal-decimal-and-binary/4133?u=alacafur

---

Which lines are equiv. to Q. 1.5, pointers worksheet?

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/arrays-vs-pointers"></iframe>

---

## Pointers Worksheet

---

### Local Variables

* Local variables are allocated in the function's *stack frame*
  * In `gdb`, `backtrace` prints list of stack frames,
  tracing from currently-executing function up to `main()`
* When a function returns, its stack frame is deallocated
  * The freed-up space on the stack can be re-used by
  a future function that is called

---

### Global Variables

* Global variables are stored in another region of memory
  * Includes read-only *string literals*
* These variables remain in memory for the entire duration
that the program is running

---

### Dynamic Memory Allocation

Dynamically allocated variables:
* Are put on the heap
* Remain allocated even after the allocating function returns

---

### Memory Model

<div class="container">
<div class="col" style="max-width:50%; margin: auto auto; vertical-align: center;">

![](./w03-figs/memory_model.svg)
<!-- .element class="stretch"-->

</div>

<div class="col" style="max-width:50%; margin: auto auto; vertical-align: center;">

Try `info proc mappings` in `gdb` to print mapped memory regions

</div>

</div>

---

### Dynamic allocation in Java

```
ArrayList createArray() {
  ArrayList a = new ArrayList()
  return a;
}
```

---

### Dynamic allocation in C:

```
int *createArray() {
  int *a = malloc(sizeof(int)*ARRAY_LEN);
  return a;
}
```

---

### Freeing Memory: Java vs. C

* Java *garbage collector* frees up memory when
an object is no longer referenced by any variable
* In C, you have to collect your own garbage
  * Use `free()` to free up allocated space that is
  no longer being used
  * Failure to do so results in *memory leaks*,
  which unnecessarily occupy space in memory

---

### Memory Leaks

![](./w03-figs/free_realestate.jpg) <!-- .element class="stretch"-->

Use `valgrind` to detect memory leaks

---

## malloc Worksheet
