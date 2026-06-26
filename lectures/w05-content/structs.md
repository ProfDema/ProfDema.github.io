### PCRS: Structures Recap

A `struct` is a collection of *members*:

```c
struct student {
    char name[21];
    int student_num;
};
```

* Can be dynamically or statically allocated
* Can declare arrays of structs, pointers to structs...
* What is `sizeof(struct student)`?
  * This is a "trick" question

---

## Structs Worksheet

---

Assuming: <code>void f(struct player p) {p.position[0] = 'D'; }</code>, what will print after <code>f(p1); printf("%s", p1.position);</code>?

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/struct-strings"></iframe>

---

### PCRS: Streams and Files Recap

* `printf` and `scanf` operate on `stdout` and `stdin`, respectively
* `stdin`, `stdout`, and `stderr` are the standard I/O streams
* But streams can be associated with an open file
* Use `fopen` and `fclose` to open and close files

---

### PCRS: Stream I/O Recap
* Functions are available to read/write on **any** stream:
  * Characters/strings: `fprintf`, `fscanf`, and `fgets`
  * Binary data: `fread`, `fwrite`
* Use `fseek` and `rewind` to *reposition* a stream
* Use `fflush` to *flush* a stream
* The man pages for all of these functions are very detailed
and informative

---

## String Literals Worksheet
