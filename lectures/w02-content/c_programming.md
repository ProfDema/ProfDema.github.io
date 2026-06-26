### Programming in C: Return Values 

`while (scanf(...) != EOF) { ... }`

* Almost every library call has a return value
* Always check return values
  * C does not throw exceptions like Java or Python
  * Rightfully be paranoid about whether or not each 
  library call completes successfully

> What does the above code do?
> Check `man 3 scanf` and scroll to `RETURN VALUE`

---

### Programming in C: Macros

* Return values are often defined as *macros*, e.g., `EOF`
  * These typically "expand" to integer constants
  * Typically defined in `.h` files
  * Already saw an example of this in PCRS:

`#define DAYS 365`

---

![](./w02-figs/forever.jpeg)

---

### Compiler Warnings (and Errors) are Your Friends

Common `gcc` compiler flags (all explained
in `man gdb`):
* `-g`: Include debugging symbols in compiled program (`gdb`
and `valgrind` make use of these)
* `-Wall`: Warn about highly-questionable code
* `-Wextra`: More warnings (sometimes helpful)
* `-Wpedantic`: All possible warnings
* `-Werror`: Treat all warnings as errors

> Your assignments **must** compile with `-Wall` and `-Werror`

---

### C: Memory (un)Safety

* C assumes that you know what you're doing
  * A perilous assumption: 
  [70% of security vulnerabilities in Microsoft products][ms]
  are due to **avoidable mistakes that C/C++ allow you to make**
* Example of unsafe code that will compile and run:
<div style="text-align: left; padding-left: 7em">
<code>int arr[10];</code><br>
<code>arr[-1] = 123;</code>
</div>

> Use `gcc` flag `-fsanitize=address` to catch memory safety bugs

[ms]: https://www.zdnet.com/article/microsoft-70-percent-of-all-security-bugs-are-memory-safety-issues/

---

### C: Undefined Behaviour

* *Undefined behaviour* is any operation for which the C standard
imposes no requirements
* Example: The contents of uninitialized variables are **undefined**
  * The following code will likely print **garbage values**,
  but **it will compile and run regardless**:

<div style="text-align: left; padding-left: 8em">
<code>int a;</code><br>
<code>printf("%d",a);</code>
</div>

> Use `valgrind` to detect reads on uninitialized variables

---

### PCRS: Arrays

Declaring arrays:

`int student_ids[400];`

Writing to or reading from array elements:

<div style="text-align: left; padding-left: 5em">
<code>student_ids[0] = 1001111111;</code><br>
<code>student_ids[399] = 1002222222;</code><br>
<code>int x = student_ids[0];</code>
</div>

Questions about these?

---

### Arrays Worksheet

---

Select the code snippets that print out `10`.
<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/pointer-basics"></iframe>

---

### PCRS: Pointers and the `&` Operator

> A *pointer* is a variable that contains the memory 
> address of another variable

1. Assume `x` is an integer and `px` is a pointer
2. Then, `px = &x` stores the *address* of `x` in `px`

The `&` operator expects its operand to be a variable
or array element, so constructs such as `&(x+1)` are illegal

---

### PCRS: Pass-by-value and Pass-by-reference

<div style="text-align: left;">
<code>int x = 10;</code><br>
<code>increment_int(x);</code><code style="color:limegreen;"> // Cannot change x</code>
<code>increment2_int(&x);</code><code style="color:limegreen;"> // Can change x</code>
</div>

`increment()` takes an *integer* parameter, whereas `increment2()` takes an *address of an integer*

---

### PCRS: Pointers and the `*` Operator

> The `*` operator interprets its operand as an address,
> and fetches the memory contents at that address

1. Assume that `y` is an integer and `px` is a pointer
2. The statement `y = *px` assigns to `y` the integer
that `px` points to

The `*` operator is said to *dereference* its operand

---

### PCRS: Declaring Pointers

Pointer declarations are intended as a mnemonic, so:

`int *px;`

means that `*px` is equivalent to a variable of type `int`.
Thus, `px` is a pointer containing the address of an `int`.

<div class="container">
<div class="col" style="max-width:38%; margin: auto auto; vertical-align: center;">

Why? Because K&amp;R.<br>(See p. 90)

</div>

<div class="col" style="max-width:40%; margin: auto auto; vertical-align: center;">

![](./w02-figs/k_and_r.jpg)
<!-- .element class="stretch" -->

</div>
<div class="col" style="max-width:20%; margin: auto auto; vertical-align: center;">

![](./w02-figs/k_and_r.svg)
<!-- .element class="stretch" -->

</div>
</div>

---

### Notes on Pointers and Addresses

* A pointer is not an array
  * But it can contain the address of an array
* An array is not a pointer
  * But the compiler interprets the name of an array as
  the address of its zeroth element, so the following
  statements are equivalent

<div style="text-align: left; padding-left: 3em">
<code>int *x = &a[0];</code><br>
<code>int *y = a;</code><code style="color:limegreen;"> // Assuming "a" is an array</code>
</div>

---

### A Common Errors With Pointers

What does this do:

<div style="text-align: left; padding-left: 5em">
<code>int *x;</code><br>
<code>*x = 10;</code><br>
</div>

What about this:

<div style="text-align: left; padding-left: 5em">
<code>int *x;</code><br>
<code>printf("%d", *x);</code><br>
</div>

**Never** dereference uninitialized (or `NULL`) pointers!

---

### Pointers Worksheet

