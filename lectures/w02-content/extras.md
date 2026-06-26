## Extra Slides

---

### Size of C Primitives

Type            | `sizeof` (bytes) | bits
----------------|------------------|-----
`char`          | 1                | 8
`int`           | 4                | 32
`long int`      | 8                | 64
`long long int` | 8                | 64

GNU C compiler (`gcc`) default values (`std=gnu11`)
on a 64-bit system. See [GNU C Reference Manual][gnucref].

[gnucref]: https://www.gnu.org/software/gnu-c-manual/

---

### Pointer Size

* On modern systems, pointers are 64 bits (8 bytes)
  * e.g., `0xFFFFFFFFFFFFFFFF`
* In memory diagrams, pay attention to whether
each "cell" represents a single byte or multiple bytes

---

### Hexadecimal, Decimal, Octal, and Binary

* A hexadecimal digit corresponds to 4 binary digits
  * `0x` prefix indicates hex, e.g., `0xFF`
  * `b` prefix indicates binary, e.g., `0b11`
* You may also encounter octal notation
  * `0` prefix, e.g., `012`
  * `\` prefix followed by up to 3 digits, e.g., `\111`
* Try declaring `int x` and assigning values in
hex, decimal, octal, and binary
* [Tutorial on binary, decimal, and hexadecimal notation][bindechex]

[bindechex]: https://linux.die.net/man/1/bin_dec_hex
