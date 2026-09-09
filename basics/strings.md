# Strings, IO, the like

## FILEIO

Note: most of the basic file io actions in C are does as system calls.
These are functions that the kernel must run, ie you are handing execution off to the kernel to resolve it.

(or rather, CPU goes into kernel mode on syscalls, allowing it to access the kernel-side of memory
mapped into that process alongside any other kernel resources needed, like file descriptor tables, pipes, redirects
vma_area_structs, TLBs, etc...)

**QUESTION**
bruh, most of these syscalls look like C, so how do programs like java handle these syscalls?
ANSWER:
CPU understands syscalls, not C. Anyways your C syscall will be translated down into machine code:

```c
read(fd, buf, n);
```
==>
```assembly
mov rax, 0       ; syscall number (a number telling the cpu which syscall you are asking for)
mov rdi, fd
mov rsi, buf
mov rdx, n
syscall          ; CPU instruction
```

**SYSCALL NUMBER** 0 -> read, 1 -> write, 2 -> open
Then, you set things up for the syscall, and running syscall moves the cpu into kernel mode, allowing the syscall to begin.

### EXE:
read(fd, buffer, 100);
===>
read(fd, buffer, 100)
       ↓
glibc
       ↓
put 0 in RAX //SYSCALL NUMBER
put fd in RDI //first register for functional parameter in SysVABI (ALL OF THE FUNCT PARAM ARE CALLER-SAVED)
put buffer in RSI //second register for functional parameter in SysVABI (RBP AND RSP ARE CALLEE-SAVED)
put 100 in RDX //third register ...
       ↓
syscall //command to execute the syscall
       ↓
kernel sees RAX = 0
       ↓
executes read


The function read(...) just facilitates this code, but in reality its the register operations









**QUESTION 2**
Cool, but where do these functions come from?

they come from various shared libraries (.so files) like libc.so, which is object code for a shared library containing
all of the basic syscalls in C, mapping the symbol "read" to the function code it corresponds to

From there, you can just access then via 
#include <unistd.h>, which is one such header containing a bunch of function prototypes, allowing you to use those functions

**NOTE** a header file is literally just a c file that defines the functions, but none of its functionality
Its just for the compiler to see that you used it correctly, as the actual mapping symbols to functions is done
later in compilation by the linker or usually even later by the dynamic linker.

```c
#ifndef HELPER
#define HELPER
void* malloc(size_t bytes);
...
#endif
```

with glibc being something like:
```c
ssize_t read(int fd, void *buf, size_t count)
{
    // put arguments in the appropriate registers
    // execute the syscall instruction
    // handle the return value
}
```

### Processes REDO:
As you recall, processes can have different files open. (note: this is different from mmaping it into the process)
The way this is handled in linux is using a file descriptor table.

This table has 2 parts:

**file descriptor** this is the integer (0,1,2,...) used to index in this table

**file description** this is the kernel-side datstructure used to represent that file, or more broadly some IO object:
a regular file
a terminal
a pipe
a TCP socket
a device like /dev/null

This struct contains information about that object, like the current file offset, file status flags (O_APPEND, O_NONBLOCK, etc.), pointer to the underlying inode or file object, and reference count.

So: 1 -> ptr to some kernel-side struct representing it

**NOTE** this table is unique to every process. What is fd1 in one process is not necessarily the same in another process

exe:
Virtual address space of Process A

+----------------------------+
|                            |
| User space                 |
|                            |
|  program code              |
|  heap                      |
|  stack                     |
|  shared libraries          |
|                            |
+----------------------------+
|                            |
| Kernel space               | (high virtual addresses, low physical addresses for kernel)
|                            |
| kernel code                |
| kernel data structures     | #like the VM_AREA_STRUCT defining that processes valid memory locations
| process tables             | ##PROCESS TABLE IS TABLE CONTAINING ALL PROCESSES RUNNING
| file descriptor tables     | # the tableS (plural) in question
| page tables                | ##PAGE TABLES DESCRIBE MEMORY (MEMORY HEIRARCHY + TLB)
| device drivers             | ## THIS TURNS THE SYSTEMCALLS AND THE KERNELS INTENTIONS INTO 
|                            | ## CODE THE PERIFERALS UNDERSTAND
+----------------------------+
You need kernel priviledges to access kernelspace ofc. (look up for how this works)

**NOTE** fork only copies userspace! 
**NOTE2** no fork / exec here, the code is inside of the executable, so no new process being created

int open(path="/path/to/file", O_WRONLY | O_CREAT | O_TRUNC)


Common File Descriptors:

stdin, stdout, and stderr are just standardized file descriptIONS used to refer to common ways of using IO in a process.
they are by default set to:
0 -> stdin (usually the keyboard)
1 -> stdout (usually the terminal / screen)
2 -> stderr (also terminal / screen, but a separate output object stream)

**KEY** READ PIPES_LEARN TO LEARN MORE ABOUT PIPES AND REDIRECT OBJECTS, BUT HERE WILL FOCUS ON FILE OBJECTS!

#### Common syscalls for this
int fd open(path="/path/to/file",flags)
This will return the file descriptor corresponding to the newly opened file. (useful bc cannot read the kernel-side table)
while CPU is in user mode.



### Useful Commands:
(stolen from C Redo)



