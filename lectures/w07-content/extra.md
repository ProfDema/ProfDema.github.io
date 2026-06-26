### Figures Credit

Figure 5-2, 6-1 and Table 27-1 are from
[The Linux Programming Interface](https://search.library.utoronto.ca/details?10030432)
by Michael Kerrisk.

---

## Extra Slides

---

### Shell Skeleton Code

```c
while (1) { // Infinite
    print_prompt();
    read_command(command, parameters);
    if (fork ()) { // Parent
        wait(&status);
    } else {
        execve(command, parameters, NULL);
    }
}
```

---

### Security Implications of Exec Functions

Using `execlp` and `execvp` can be very dangerous
when used improperly. Can you find out why?

Hint: See Section 27.2.1 of
[The Linux Programming Interface](https://search.library.utoronto.ca/details?10030432)
by Michael Kerrisk.
 
