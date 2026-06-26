### CSC209: Software Tools and Systems Programming
#### Week 1: Introduction to UNIX

[Furkan Alaca](https://mcs.utm.utoronto.ca/~alacafur/), Ilir Dema, [Andrew Petersen](https://utmandrew.bitbucket.io/)

>Required Reading: Chapter 2 of <u>Unix Shell Programming</u> by Kochan &amp; Wood

---

### What is This Course About?
* Systems programming with a UNIX focus:
  * The file system
  * Process management
  * System calls
  * Inter-process communication
* C is our programming language of choice
  * Other systems-level languages exist, e.g., C++, Go

---

### What is This Course About? (2)
* Programming tools: Develop more efficiently
  * Debugging tools: gdb, valgrind, strace, ltrace
  * Build automation tools: make
  * Version control: git
* Interacting with a UNIX-like OS using the Bash shell

notes:
With the help of these tools, you will spend less time debugging, more time being productive.

---

### UNIX vs. Linux vs. UNIX-like
* UNIX is a proprietary OS developed by AT&T in 1969
* Free and commercial imitations followed, such as BSD, Linux, Solaris
  * The macOS kernel is a BSD derivative
* We say UNIX to refer to *UNIX-like* OSs, often colloquially called <em>\*nix</em>
* Linux is the most widely-used UNIX-like OS: It runs on all kinds of devices, e.g., PCs, smartphones, printers, security cameras, wireless routers...

---

### The UNIX Timeline

![](w01-figs/unix_timeline.svg) <!-- .element width="72%" -->

---

### GNU/Linux: User Space vs. Kernel Space
![](w01-figs/user_kernel.svg) <!-- .element width="55%" -->

---

### After taking this course, you should be able to...
* Diagram and explain the memory usage/layout of an arbitrary C program
* Write programs that leverage the Linux kernel interface, GNU C library, and GNU C compiler to:
  * Perform low-level I/O, process management, and inter-process communication (local & networked)
  * Adhere to the UNIX philosophy
* Read the man page of an unfamiliar system call or library function and be able to understand and use it
* Use standard UNIX development tools and command-line utilities

---

### A Typical Week in CSC209
* <em>Prepare</em> for class in advance
  * Watch videos on [PCRS](https://pcrs.teach.cs.toronto.edu/) to familiarize yourself with concepts
  * Solve simple exercises (worth marks)
  * Note down your questions
* <em>Participate</em> in class to consolidate and deepen your knowledge by:
  * Practising more advanced exercises
  * Asking questions
* <em>Apply</em> your knowledge on assignments and tutorials

---

### Course Evaluation Scheme 
* 5%: Weekly lecture prep (due 10pm on Sundays)
* 10%: Weekly tutorials (due 10pm on Fridays)
* 3%: Participation
* 5%: Assignment 1 (C Basics and Pointers)
* 9%: Assignment 2 (System Calls, Dynamic Memory)
* 9%: Assignment 3 (Processes)
* 9%: Assignment 4 (Communication)
* 10%: Midterm Exam (Mon. Mar. 2, 7:10pm)
* 40%: Final Exam (Min. 40% required to pass course)

---

### Assignment and Tutorial Submission
* Assignments will be submitted over git
* Repositories will be managed on [MarkUs](https:/mcsmark.utm.utoronto.ca/csc209s19)
* Each assignment or tutorial will have its own directory in your repo
  * Starter code will be pushed to your repo
* Feedback and marks will be pushed to your repos

---

### Assignment/Tutorial Grading
* Assignment grading will be automated
* Be careful with:
  * Required file names
  * Directory structure
  * Output format
    * "Hello, world!" is not equivalent to "Hello, World!" or "Hello, world! " (spot the differences)
* **Code that does not compile will receive a grade of zero**

---

<img src="w01-figs/compile_errors.jpeg"/>

---

### Testing Your Assignments/Tutorials
* Ensure that your code compiles without warnings and errors
* It is necessary, but not sufficient, that your code runs without crashing the lab PCs
* Use the necessary debugging tools to ensure that your program is free of errors that may cause it to:
  * Work on one PC, crash on another PC
  * Work on some runs, crash on other runs, even on the same PC

---

### Assignment Resubmission
* We will send you feedback in the form of test results soon after the submission deadline
  * The feedback is not your mark
  * You will have 48 hours after receiving the feedback to correct the errors and resubmit
* Grades will be determined using a weighting scheme on the test results
* Your assignment will receive the higher of:
  * The grade on the original submission
  * The grade on the resubmission, with a 10% deduction

---

### Academic Integrity
> The work you submit must be your own, done without participation by others. It is an academic offence to hand in anything written by someone else without acknowledgement.

---

### Academic Integrity Don'ts: 
* Looking at another student's assignment
* Using code that you haven't written, without attribution
* Asking someone else (e.g., classmate or stranger on Stack Overflow) to write your code
* You are not helping your friend when you give them a copy of your assignment
* You are hurting your friend when you ask them to give you a copy of their assignment

---

### Do Help Each Other by:
* Explaining and/or clarifying concepts
* Reviewing/modifying/practicing exercises from PCRS, lectures, and previous weeks' tutorials together
* Helping each other understand documentation, error messages

> Give a man a fish and feed him for a day. Teach a man to fish and you feed him for a lifetime.

---

### How to Get Support
* Use the [Discussion Board](https://mcs.utm.utoronto.ca/forum/)
  * Ask questions about course content here (not by e-mail), so all students can benefit
* Form an [FSG](https://www.utm.utoronto.ca/asc/facilitated-study-groups-fsgs)
* Office Hours
* Go to tutorials, ask questions to your TAs
  * Don't ask TAs "How do I do the assignment?"
  * Ask questions to understand tools/concepts needed for completing the assignment, common mistakes, debugging techniques, etc.

---

### Preparing for CSC209: Linux
* This course assumes basic familiarity with Linux
* Get accustomed to using a text editor on Linux
* Familiarize yourself with basic shell commands/utilities
* Learn to ssh into the lab machines to work remotely
* Install a Linux virtual machine on your PC (even better: dual-boot)

![](w01-figs/nmap_trinity.png) <!-- .element width="50%" -->

---

### C Programming
* This is not a C programming course
* We will use C, and learn some key concepts in C
* After taking this course, you should just as easily be able to learn another language (like Go) and accomplish the same goals
* Java (which you learned in CSC207) syntax was designed to be familiar to C programmers

---

### Preview of What's Next
* This week: UNIX shell and compiling C programs
  * Tutorial 1 is due Friday Jan. 10 at 10pm
* Next week: Arrays and pointers
  * Class prep is due Sunday Jan. 12 at 10pm 
  * Tutorial 2 will be due next Friday Jan. 17 at 10pm
* Assignment 1 will be posted next week
