### Bitwise Operations

Working with FDs and signals requires us to be
familiar with some bit operations, namely:

1. Shift operators
2. Bitwise `AND`, `OR`, `NOT`, and `XOR` operators
3. Using bitwise operators to *set* and *clear* bits

---

### Bitwise Left Shift Operator

`i << j` shifts bits in `i` to left by `j` places
  * The right-hand-side is filled with `0` bits

```c
unsigned char i, j;
i = 13;      /* binary 00001101 */
j = i << 2;  /* binary 00110100 */
```

---

### Bitwise Right Shift Operator

`i >> j` shifts bits in `i` to the right by `j` places
  * The left-hand-side is filled with `0` bits if `i` is *positive*
  * The left-hand-side is filled with `1` bits if `i` is *negative*

```c
unsigned char i, j;
i = 13;      /* binary 00001101 */
j = i >> 2;  /* binary 00000011 */
```

```c
char k, l;
k = -128;    /* binary 10000000 */
l = k >> 2;  /* binary 11100000 */
```

---

### Bitwise AND

```c
char i, j, k;
i = 21;     /* binary 00010101 */
j = 56;     /* binary 00111000 */
k = i & j;  /* binary 00010000 */
```

---

### Bitwise OR

```c
char i, j, k;
i = 21;     /* binary 00010101 */
j = 56;     /* binary 00111000 */
k = i | j;  /* binary 00111101 */
```

---

### Bitwise NOT

```c
char i, j;
i = 21;  /* binary 00010101 */
j = ~i;  /* binary 11101010 */
```

---

### Bitwise XOR

```c
char i, j, k;
i = 21;     /* binary 00010101 */
j = 56;     /* binary 00111000 */
k = i ^ j;  /* binary 00101101 */
```

---

### Convention for Numbering Bits

Convention for referring to specific bits is to number them from the
right-hand-side, e.g., a char consists of 8 bits, starting from `b0`
on the right-most (i.e., *least significant* or *low-order*) bit:

`b7 b6 b5 b4 b3 b2 b1 b0`

---

### Setting Bits

To *set* bit 4 of integer `n` (i.e., set value of bit 4 to `1`):

`n = n | (1 << 4)`

or

`n = n | 16`

or

`n |= 16`

---

### Clearing Bits

To *clear* bit 3 of integer `n` (i.e., set value of bit 3 to `0`):

`n = n & ~(1 << 3)`

or

`n = n & ~8`

---

### Exercise (Homework)

How can you test whether bit `i` is set in integer `n`?

---

### Exercise

What is the value of `n` if `int n = 10 & ~8;`?

<iframe class="stretch" frameborder="0" scrolling="no" data-src="https://mcs.utm.utoronto.ca/~alacafur/courses/simple-vote-209/poll/bitwise"></iframe>
