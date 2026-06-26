# Extra Slides

---

### UNIX File Systems

![](w01-figs/unix_files.svg) <!-- .element width="90%" -->

---

### Files and inodes

* In UNIX, every file is associated with an *inode*
* An *inode* is a structure that contains key information about
the file, including:
  * A unique numeric ID
  * Access permissions
  * Owning user and group

---

### Directory Entries and Links

* A *directory* is a file containing *directory entries*
* A *directory entry* maps a *file name* to an *inode number*
* *Hard links* refer to directory entries that assign one or
more file names to the same inode number
* A *symbolic link* is a file that contains a reference to
a *file path*, i.e., to a directory entry

---

### Hard Links
* *Hard links* refer to multiple file names that map to the same inode
  * Each inode thus has a *link count*
* Removing a file involves deleting a directory entry, which:
  * *Unlinks* that file name from the inode
  * Decrements the corresponding inode's link count
  * If the link count is 0, the inode and associated file data is deleted
* `.` and `..` are hard links present in every directory
  * What is a directory's minimum link count?

---

### Job Control

* Jobs are programs that were started in the shell
* <kbd>ctrl+z</kbd> suspends the *foreground job* 
* Append `&` to a command to start a *background job*
  * e.g., <kbd>./hello&</kbd>
  * Background jobs are killed if the terminal is closed
* <kbd>jobs</kbd> lists the status of jobs in the current session
* <kbd>fg <em>N</em></kbd> resumes job number *N* in the foreground
* <kbd>bg <em>N</em></kbd> resumes job number *N* in the background
* <kbd>kill &percnt;<em>N</em></kbd> kills job number *N*

---

### Typographical Conventions in Slides

* Commands to be typed: <kbd>ping utoronto.ca</kbd>
* Code fragments, commands, function names, variables: `printf`
* File names:
  * When part of commands/code: Same as `code`
  * Other contexts: *emphasized*
* New terms: *emphasized*
* Book titles: <u>underlined</u>

