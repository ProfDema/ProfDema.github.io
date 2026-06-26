### PCRS: Strings Summary

* In C, a string is an array of `char`s terminated by `\0` (`NULL` byte)
* C standard library offers string manipulation functions, defined in `string.h`

---

### String Manipulation and Memory Safety

* String manipulation is a major cause of memory errors (e.g., *buffer overflow*)
* The C standard library includes both *safe* and *unsafe* string functions
  * **Some** unsafe functions can be used safely if 
  the string is **guaranteed** to be NULL-terminated:<br>
  `strlen(argv[0]);`
  * But even so-called "safe" functions can cause memory errors if used
  improperly:<br>
  `char x[2]; strncpy(x, "blabla", 7);`

---

### Unsafe String Functions: Example

From `man gets`:

> Never use gets().  Because it is impossible to tell without knowing the
> data  in  advance  how  many  characters  gets() will read, and because
> gets() will continue to store characters past the end of the buffer, it
> is  extremely  dangerous  to  use.   It has been used to break computer
> security.  Use fgets() instead.

---

### Unsafe String Functions & Security

* *Question*: How can an attacker exploit a buffer overflow to break a system's security?
* *Answer*: [Check out this CSC347 tutorial](https://mcs.utm.utoronto.ca/~alacafur/courses/csc347_f19/tutorials/t8.shtml)
* *Real example*: [Recent WhatsApp vulnerability](https://arstechnica.com/information-technology/2019/05/whatsapp-vulnerability-exploited-to-infect-phones-with-israeli-spyware/)
* *Lessons*:
  * Only use C when necessary, and be mindful of safe programming practices
  * Otherwise, be responsible and use a safe language

---

![](./w04-figs/safe_functions.png)

---

<span class="container">
<div class="col" style="margin: auto auto;">

What is the difference between
the bottom two squares?

Hint: See `man strncpy` and
`man strncat`

</div>

<div class="col" style="max-width:40%;">

![](./w04-figs/strcpy_meme.png)

</div>
</span>

---

Select the *memory-safe* code snippets.

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/string-safety"></iframe>

---

![](./w04-figs/printf_string.jpeg)

---

## Malloc and Strings Worksheet

---

## Command-line Arguments Worksheet
