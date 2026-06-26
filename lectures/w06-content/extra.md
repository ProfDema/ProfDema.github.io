## Extra Slides

---

### Reference on Function Declaration vs. Definition
 
* [Function Declarations](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Function-Declarations) 
* [Function Definitions](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Function-Definitions) 

---

### Struct Padding

Running the sample code below, you can observe how the compiler adds
padding bytes to structs to make them align with word boundaries.

[The GNU C Reference Manual explains why this is done][gnuc_structs].
See what happens when this behaviour is disabled
by compiling with `-fpack-struct`.

```c
#include <stdio.h>

struct test {
	char b;
	int a;
};

int main() {
	struct test a[10];
	printf("Address of first element: %p\n", &a[0]);
    printf("Address of second element: %p\n", &a[1]);
    printf("Address of third element: %p\n\n", &a[2]);
	printf("Address of char in the struct: %p\n", &(a[0].b));
    printf("Address of int in the struct: %p\n\n", &(a[0].a));
	printf("Size of struct array: %ld\n", sizeof(a));
	return 0;
}
```
<!-- .element class="stretch" -->

[gnuc_structs]: https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Size-of-Structures
