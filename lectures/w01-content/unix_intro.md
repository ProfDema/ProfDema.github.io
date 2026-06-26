### The UNIX Philosophy
Brief summary of the [UNIX philosophy](https://en.wikipedia.org/wiki/Unix_philosophy), from <u>A Quarter-Century of UNIX</u> by P. H. Salus, 1994:
* Write programs that do one thing and do it well
* Write programs to work together
  * Expect that the output from your program will be used as input for another (e.g., by piping)
  * Don't require interactive input
* Write programs that handle text streams, because that is a universal interface

---

### Common UNIX Tools/Commands and Abstractions

| File/directory operations | Text filtering | System Information | Input/Output Abstractions  |
|---------------------------|----------------|--------------------|----------------------------|
| `cd`, `ls`                | `head`         | `who`, `last`      | stdin                      |
| `mkdir`                   | `tail`         | `free`             | stdout                     |
| `touch`                   | `sort`         | `ps`               | stderr                     |
| `cp`, `mv`, `rm`          | `grep`         | `top`              | pipes/fifos                |
| `cat`, `diff`             | `tr`, `wc`     | `type`             | sockets                    |
|                           |                |                    |                            |

Look these up in the man pages for practice!

---

### How to Learn Linux
**Use it.**
* Don't worry about memorizing stuff
* Work on your task(s) at hand, look things up as needed
  * [Man pages](http://man7.org/linux/man-pages/): Comprehensive documentation
  * [Arch Wiki](https://wiki.archlinux.org/): Community-maintained tutorials
* Common tasks will quickly start to become familiar
* A key outcome of your CS degree: Being able to quickly locate the required information to learn new concepts on your own

---

![](w01-figs/man_answer.jpeg) <!-- .element width="40%" -->

---

### Man pages
* The man pages are sectioned; you will mainly use:
  * 1: General commands
    * e.g., <kbd>man ls</kbd> to learn how to use <kbd>ls</kbd>
  * 2: System calls
  * 3: Library functions
  * 7: Miscellanea
    * e.g., <kbd>man gittutorial</kbd> or <kbd>man man-pages</kbd> <!--for an introduction to git or man pages, respectively-->
* If the command exists in more than one section, specify the section you want:
  * e.g., <kbd>man 3 printf</kbd> for the `printf` library function, <kbd>man 1 printf</kbd> for the `printf` shell command

---

Even the `man` command has its own man page: <kbd>man man</kbd>

![](w01-figs/man_man.jpeg) <!-- .element width="45%" -->

You likely won't use any special options, aside from <kbd>man -k</kbd> or <kbd>man -K</kbd> (to search); <kbd>man man-pages</kbd> will be more generally informative.

---

### The Shell Prompt

`$ gcc -o hello hello.c`

* The `$` is a *prompt* indicating that the user can enter a command via keyboard input
* Commands can be shell builtins (e.g., `cd`, `ls`, `type`)
  * Check <kbd>man builtins</kbd>
* Commands may also launch an executable file, by providing either:
  * The full path to the executable file
  * The name of the executable file; the shell will search for the file in the directories listed in the `PATH` environment variable

---

### Executing Programs in the Shell

<div style="text-align: left; padding-left: 6em">
<code>$ gcc -o hello hello.c</code><br/>
<code>$ ./hello</code>
</div>

* The first line compiles the C program <code>hello.c</code> into an executable file <code>hello</code>
* The second line tells the OS to load the <code>hello</code> program into memory and jump to its *entry point*
  * C compiles to *machine code*
  * Recall CSC207: Java compiles to *bytecode*
* Let's see how the executable file is loaded into memory...

---

### Memory Model

<span class="container">
<div class="col" style="max-width:40%">

* Memory is divided into *segments*
* The executable program code is loaded into the bottom segments:
  * Read/write data
  * Read-only code and data

</div>

<div class="col">

<img src="w01-figs/memory_model.png"/>

</div>
</span>

---

### Did You Notice?

<div style="text-align: left; padding-left: 6em">
<code>$ gcc -o hello hello.c</code><br/>
<code>$ ./hello</code>
</div>

* Q: Why is `hello` prefixed by `./`, but not `gcc`?
  * A: Current directory is not included in `PATH`
* **Pay attention to detail**: Understand the meaning behind every character
* Even missing (or extra) spaces can cause you hours of grief

---

![](w01-figs/me_compiler.jpeg) <!-- .element width="50%" -->

Avoid spamming `gcc` with code until it compiles: Compilers catch syntax errors, but not logical flaws

---

### The UNIX File System Hierarchy

![](w01-figs/unix_fs_tree.svg)

---

### File System Hierarchy on Lab PCs

* On most UNIX systems, a user `bob`'s home directory is `/home/bob`
  * But on the lab PCs, it is `/student/bob`
* Devices or networked file systems can be *mounted* to directories in your file system tree
  * Your home directory is mounted from the MCS server
  * Run <kbd>df</kbd> to see list of mounted devices and network locations

---

### Absolute File Paths
`/usr/bin/bash`

* Above: Path to the executable file `bash` (our shell program)
* The leading `/` represents the *root directory*
* `usr` is a *subdirectory* of `/`
* `bin` is a subdirectory of `usr`
* `bash` is a file located in `bin`
* The `~` shortcut translates (*expands*) to your home directory, e.g., try <kbd>cd ~/my_git_repo</kbd>

---

### Relative File Paths

* You may also access files *relative* to your *present working directory*
  * `./file1` refers to `file1` in your working directory
  * `../file2` refers to `file2` in the *parent* of your working directory
  * `../../file3` refers to `file3` in... you get the idea
* Run <kbd>pwd</kbd> to see your present working directory

---

### What is a Directory?

* A directory is a file that contains *directory entries*
* Directory entries map files names to *inode* numbers
* An inode is a data structure containing information about a file, such as its:
  * Access permissions
  * Size
  * Physical location on-disk

---

### Directory Entries and inodes

![](w01-figs/inodes.svg)

---

### Files in UNIX

* "[Everything is a File](https://en.wikipedia.org/wiki/Everything_is_a_file)" is a key UNIX feature
  * Files and processes: Principal UNIX abstractions
* UNIX provides a file interface for all Input/Output:
  * Regular files
  * Directories
  * Special files (e.g., `/dev/null`, `/dev/urandom`)
  * Physical Devices (e.g., keyboard, mouse, printer)
    * Try <kbd>cat /dev/urandom | padsp tee /dev/audio > /dev/null</kbd> with your volume turned up
  * Pipes for inter-process communication
  * Network sockets

---

### Output Redirection

* Standard I/O streams that every process starts with:
  * `stdin`: By default, reads input from keyboard
  * `stdout`: By default, writes to the console display
  * `stderr`: By default, writes to the console display
* The process treats these streams as files (surprise!)
* Use `>` to *redirect* `stdout`, and `2>` to redirect `stderr`
  * `>` overwrites the output file, `>>` appends
  * e.g., try <kbd>ls &gt;myfiles.txt</kbd>
* Refer to [Section 5.1: Simple redirections](https://linux.die.net/Intro-Linux/sect_05_01.html), <u>Introduction to Linux</u>
<!--* [Good online tutorial with more examples](https://www.tutorialspoint.com/unix/unix-io-redirections.htm)-->

---

### Pipes and Process Substitution

* *Pipes* transfer output from one process to another
  * e.g., <kbd>ls | grep "pdf"</kbd>
* *Input redirection* transfers the contents of a file into `stdin` of a process
  * e.g., <kbd>wc &lt;essay.txt</kbd>
* *Process substitution* creates a *temporary file* to transfer the output from one or more processes to `stdin` of another process
  * e.g., <kbd>wc &lt;(ls)</kbd> or <kbd>wc &lt;(ls | grep "pdf")</kbd>
* Refer to [Chapter 23: Process substitution](http://tldp.org/LDP/abs/html/process-sub.html), <u>Advanced Bash-Scripting Guide</u>

---

### UNIX File Permissions

![](w01-figs/file_perms.svg) <!-- .element width="40%" -->

* Each file has a permission string, e.g., `-rwr-xr-x`
* `rwx` flags represent *read*, *write*, &amp; *execute* permissions
* Separate permissions are assigned to three categories of users:
  * The file's owning *user*
  * The file's owning *group*
  * All *other* users

---

### UNIX File Permissions: Directories

![](w01-figs/file_perms.svg) <!-- .element width="40%" -->

* First column: `d` (directory), `l` (link), or `-` (regular file)
* For directories: `r` allows listing its contents (`ls`), `w` allows creating/deleting directory entries, `x` allows entering the directory (`cd`)

---

### Symbolic Links

* *Symbolic links* are files that contains a reference to another file name (i.e., directory entry)
* In Windows terminology, a shortcut:

![](w01-figs/shortcut.png) <!-- .element width="40%" -->

---

### Hidden Files

<!-- selecting python highlighting below,
as a hack to avoid "test" being highlighted -->
```python
$ ls
file1  file2  file3  test1  test2

$ ls -a
.  ..  file1  file2  file3  .hidden  test1  test2
```

Files prefixed by a `.` are *hidden* files

---

### Interpreting Directory Listings

<!-- selecting python highlighting below,
as a hack to avoid "test" being highlighted -->
```python
$ ls -la
total 16
drwxr-xr-x 4 bob staff 4096 Jan  6 20:18 .
drwxr-xr-x 3 bob staff 4096 Jan  6 20:18 ..
-rw-r--r-- 1 bob staff    0 Jan  6 20:16 file1
-rw-r--r-- 1 bob staff    0 Jan  6 20:17 file2
lrwxrwxrwx 1 bob staff    5 Jan  6 20:17 file3 -> file2
-rw-r--r-- 1 bob staff    0 Jan  6 20:18 .hidden
drwxr-xr-x 2 bob staff 4096 Jan  6 20:16 test1
drwxr-xr-x 2 bob staff 8192 Jan  6 20:16 test2
$
```
* From left to right: file permissions, link count, owning user, owning group, file size, last modified date, and file name (symbolic link indicated by `->`)
* <kbd>ls -ali</kbd> shows inode numbers in the first column

---

### Changing File Permissions

* The file owner (or root user) can change a file's permissions with `chmod`
  * e.g., <kbd>chmod o+r file.txt</kbd> grants all users permission to read `file.txt`
* Octal notation: For each user category, add up the values for `r` (4), `w` (2), and `x` (1)
  * e.g., <kbd>chmod 754 file.txt</kbd> grants:
    * `rwx` to the owning user
    * `rx` to the owning group
    * `r` to all other users
* Exercise: <kbd>man chmod</kbd> for more `chmod` usage examples

---

### Globbing

* *Globbing* patterns are strings that expand to match multiple file names
  * Similar, but simpler, than regex: see <kbd>man 7 glob</kbd>
* `?` matches any single character
* `*` matches any string, including the empty string
* `[list of characters]` matches a single character inside the list, e.g., `[abc]`
* Usage examples:
  * <kbd>rm \*.log</kbd>: Remove all files ending in `.log`
  * <kbd>ls \*.pdf</kbd>: List files ending in `.pdf`

