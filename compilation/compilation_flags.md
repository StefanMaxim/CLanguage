# Compilation and its flags:

## rewrite later:

GCC:
a compiler that translate source code in c to machine code for Computer
(technically, compiler takes it to assembly, then assembler and finally linked)
so chain is:
pre-processor, compiler, assembler, linker, executable


compiler flags:
`> gcc -std=c99 -g -Wall -Wextra -Wshadow --pedantic -Wvla -Werror`

std=c89 means use the 1989 standard for c

-Wall means give you all the compiler warnings

-Wshandow means it warns you of shadow variables, ie when a variable of the same name is defined
in local and global scope, with that making it confusing to which you are referring
(granted it will allways take the one in local scope, but still confusing)

--pedandic means it will restrict the c standard, so no single line comments or that type of stuff

-Wvla means will warn you of any variable length arrays, enforcing that you use only fixed length ones

-Werror means treating warnings as errors (ie cannot compile unless no warnings)


### Headers
(read linking intro for this)
**NOTE**: when compiling a file which uses code from multiple files, need to be sure the compiler knows the signature of
the function, ie how many params and what type

TO DO THIS, use a header file, essentially a file where you declare the stuff you will be using just so it knows what to look for

ie when using a function in foo.c that is defined in bar.C

#include<stdio.h> // <> means search the standard/system libraries for this header file
#include "bar.h" // "" means search current/source directory first, then standard (can add directories to include path)






HOW TO COMBINE THEM???

FIRST, compile each source file separately into object files (foo.o), which is binary code, but not fully executable as
its missing context

(gcc -c foo.c) which outputs (foo.o)

SECOND, we will link the compiled object files together using gcc:

(gcc foo.o bar.o -o out) which combines the two object files into an executable called (out)


**KEY**
### WHOLE PIPELINE:
C source -> preprocessed c -> assembly -> object -> linked executable

gcc -E main.c -o main.i (this gets you to the pro-processed version only)

gcc -E -P main.c -o main.i (this removes the line markers)

gcc -S main.c -o main.s (this gives it to you in assembly)
where:
gcc -S -masm=intel main.c main.s (this is the intel syntax)

gcc -c main.c -o main.o (the object version) view with 

gcc main.o -o main (this si the final output)
or in one step:
gcc main.c -o main

LOOK AT THE EXECUTABLES VIA:
readelf -h ./program //shows file header, containing overall properties and file info
readelf -S ./program //shows section headers (not loader segments)
readelf -l ./program //shows program segments (chunks the loader uses to shove things into the process) (program headers)
readelf -d ./program //shows info for the dynamic linker, ie what dlinker does with this binary
readelf -s ./program //shows symbol table


for linux, and for mac:

otool -hv ./program       # Mach-O header
otool -l ./program        # load commands / segments
otool -L ./program        # linked dynamic libraries
otool -Iv ./program       # indirect symbols
nm ./program              # symbols

ELF looks like:
ELF header
  ├── program headers
  ├── section headers
  ├── .text
  ├── .data
  ├── .dynsym
  ├── .dynamic
  └── ...

MachO looks like:
Mach-O header
  ├── load commands
  │    ├── LC_SEGMENT_64
  │    ├── LC_LOAD_DYLIB
  │    ├── LC_SYMTAB
  │    ├── LC_DYLD_INFO
  │    ├── LC_RPATH
  │    └── ...
  ├── __TEXT
  │    ├── __text
  │    ├── __cstring
  │    └── ...
  ├── __DATA
  └── ...

Overall idea:
source code
   ↓
compiler
   ↓
object files (.o)
   ↓
LINKER
   ↓
executable / shared library
   ↓
LOADER
   ↓
program mapped into memory
   ↓
DYNAMIC LINKER
   ↓
shared libraries + symbols resolved
   ↓
main()


1. Linker: at build time:
clang main.o foo.o -o program //linker combines the function call in main with the function definition in foo
The linker does things like:

combine object files
resolve symbols
assign addresses
lay out sections/segments
perform relocations
produce an executable or shared library

if main calls print(), which is defined in some other file, be it a .o or some static lib
(ld or clangs lld work here on linux, ld64 on mac)


2. Loader:
this is what takes the executable file, and loads it into memory (the process's virtual memory space)
(execve() calls the loader)

The loader is responsible for things such as:

reading the executable format
creating the process address space
mapping executable segments into memory
setting memory permissions
setting up the stack
establishing the initial CPU state
arranging for the dynamic linker to run when necessary

on linux, executable specifies a loader, usually /lib64/ld-linux-x86-64.so.2
on mac, same thing, usually /usr/lib/dyld

3. Dynamic Linker
at runtime, suppose want function print(), buts its not defined in the executable.
it does however know it wants the function print() and that its in libc (dynamic library, read linking intro)
**KEY**(this is the same executable as the loader!) IT DOES BOTH: LOADS THE EXECUTABLE INTO MEMORY AND MAPS OTHERS
THAT ARE NEEDED

difference is instead of making a massive executable, just draw them into the process on runtime when needed, adn then
get rid of. THis way, it saves space