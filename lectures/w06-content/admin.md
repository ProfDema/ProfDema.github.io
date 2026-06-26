### CSC209: Software Tools and Systems Programming
#### Week 6: Makefiles

[Furkan Alaca](https://mcs.utm.utoronto.ca/~alacafur/), Ilir Dema, [Andrew Petersen](https://utmandrew.bitbucket.io/)

---

### C Programming vs. Systems Programming

* Now you know C and its key features
  * Still some features we have not yet worked with,
  e.g., [enums](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Enumerations)
  and [unions](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Unions)
* Many *concepts* covered so far, e.g., pointers and
pointer arithmetic, are universal to systems-level programming

---

### Pointers and the Memory Model

* You should now have a complete understanding of pointers and
the memory model
* So, the mistakes in the upcoming slides should be
obvious to you

---

### Use After Return

```c
int *foo() {
  int a = 10;
  return &a;
}

int main() {
  int *b = foo();
  printf("%d", *b);
  return 0;
}
```

[More info on Address Sanitizer Wiki](https://github.com/google/sanitizers/wiki/AddressSanitizerUseAfterReturn)

---

### Use After Scope

```c
int main() {
  int *b;
  for (int i = 0; i < 10; i++) {
    b = &i;
  }
  printf("%d", *b);
  return 0;
}
```

[More info on Address Sanitizer Wiki](https://github.com/google/sanitizers/wiki/AddressSanitizerUseAfterScope)

---

### Takeaways

* Understand when memory is allocated and deallocated in your program
  * Non-static variables are *automatically* allocated/freed
  [upon entering/exiting scope](http://port70.net/~nsz/c/c11/n1570.html#6.2.4p6)
  * Dynamically-allocated memory is your responsibility to 
  allocate/free
* [Familiarize yourself with complete list of errors that Address Sanitizer detects][ASan]
* [Understand how C syntax translates to what the system actually does under the hood][c_syntax]

[ASan]: https://github.com/google/sanitizers/wiki/AddressSanitizer
[c_syntax]: https://mcsapps.utm.utoronto.ca/forum/t/demystifying-declaration-initialization-and-assignment-in-c/4789

---

### Systems Programming

* Now we will shift to the *systems-level* aspect of the course,
which requires awareness of the hardware
and operating system being used
  * Unlike Java or Python, which act as a "translation layer"
  that make all platforms appear similar
* When working on tutorials/assignments, think about what
we're learning about the underlying system

---

## Wrap-Up: Structs & Inspecting Executables Worksheets
