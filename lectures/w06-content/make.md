Which assignment was easier?

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/easier-assign"></iframe>

---

### PCRS Recap: Compiling C Programs

* C programs can consist of multiple `.c` files
* Each individual `.c` file can be compiled to an *object file*
* Object files contain "placeholders" for addresses
of functions that were *declared* but not *defined*
  * Header (`.h`) files ensure consistency between function
  declarations across your program's multiple source files
* The *linker* connects object files together to create
an *executable file*

---

### PCRS Recap: Makefiles

* Makefiles facilitate *building* 
(i.e., compiling, linking, sometimes testing and packaging)
projects consisting of multiple source files
* If only one source file has changed, no need to recompile
everything; instead:
  1. Recompile source files that have changed
  2. Relink updated object files to generate new executable file

---

### Makefile format

A Makefile contains a sequence of *rules*, each in the format:

```
target: prereq_1 prereq_2 ... prereq_n
    action_1
    ...
    action_n
```

---

### PCRS Recap: Using make

* Makefiles are processed by the `make` program
* Run `make` with no arguments to evaluate first rule
* Run `make TARGET` to execute action(s)
defined in rule for `TARGET`
  * Only if `TARGET` prerequisites were modified since
  last time that `make TARGET` was run
* To force `make TARGET` to recompile code, either:
  * Update last modified time of prerequisite source files, with `touch`
  * Delete prerequisite object files

---

### Makefile Syntax: Defining Variables

You may define variables to, e.g., store compiler flags:

```makefile
CFLAGS= -g -Wall -Werror -fsanitize=address
reverse : reverse.c
    gcc $(CFLAGS) -o reverse reverse.c
```

---

### Makefile Syntax: Automatic (Built-In) Variables

| Variable | Meaning                       |
|----------|-------------------------------|
| `$@`     | Target                        |
| `$<`     | First prerequisite            |
| `$?`     | All out of date prerequisites |
| `$^`     | All prerequisites             |

```
CFLAGS= -g -Wall -Werror -fsanitize=address
hello: hello.c hello.h
    gcc $(CFLAGS) -o $@ $<
```

Ref.: [10.5.3: Automatic Variables, GNU Make manual](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html)

---

### Makefile Example (Assignment 2)

```makefile
FLAGS= -Wall -Werror -fsanitize=address -g
OBJ = simfs.o initfs.o printfs.o simfs_ops.o
DEPENDENCIES = simfs.h simfstypes.h

all : simfs

simfs : ${OBJ}
    gcc ${FLAGS} -o $@ $^

%.o : %.c ${DEPENDENCIES}
    gcc ${FLAGS} -c $<

clean :
    rm -f *.o simfs
```

---

### Makefile Example: Pattern Rules

```makefile
%.o : %.c ${DEPENDENCIES}
    gcc ${FLAGS} -c $<
```

* Most files are compiled in the same way, so we write
a pattern rule for the general case
* `%` expands to the stem of the file name (i.e., without extension)
* `gcc -c` compiles the source file(s), but does not link

---

### Makefile Example: Phony Targets

You may want a command that builds a number of other targets:<br>
<div style="text-align: left; padding-left: 0em">
<code>OBJ = simfs.o initfs.o printfs.o simfs_ops.o</code><br>
<code>simfs: ${OBJ}</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;gcc ${FLAGS} -o $@ $^</code>
</div>

Or a target that doesn't build anything:<br>
<div style="text-align: left; padding-left: 0em">
<code>clean:</code><br>
<code>&nbsp;&nbsp;&nbsp;&nbsp;rm -f &ast;.o simfs</code>
</div>

---

## Makefiles Worksheet
