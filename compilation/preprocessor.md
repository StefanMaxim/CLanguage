# pre-processor


## change later

### Conditional Compilation
NOW FOR THE CONDITIONAL COMPILATION:

#if
#ifdef
#ifndef
#elif
#else
#endif
#define
#undef



1. #define
#define is used for defining a constant expression. This is known as a **preprocessor directive** meaning that it exists
only for the eyes of the pre-processor, and will not remain in the final code.

#define ZERO 0 //this is the general format, defining the constant expression "ZERO" to expand to "0" whereever it is in the code:

Thus, an expression like:

"ZERO > 5" will become "0>5" in the actual code

**NOTE**
can also use bare:
#define DEBUG //here, debug expands to "" (NOTHING), but is still defined

2. #undef
This un-defines the macro mid-code. confusing but but potentially useful
#undef DEBUG




3.  #if is used to check whether some **constant expression** evaluates to 0:
    if 0, then false, else true

#if 1
    printf("This gets compiled");
#endif

#if 0
    printf("This doesn't");
#endif

**NOTE** this also works on full expressions:

#define EXP 3+4*5

#if EXP > 4 //THIS WORKS PERFECTLY FINE
#endif 

HOWEVER, DOESNT WORK WITH C VARIABLES:
int x = 4;
#if x > 0 //THIS WILL FAIL: because the preprocessor doesnt know about c variables
#endif

FOR non-defined:
#define DEBUG
#if DEBUG //UNDEFINED IS TREATED AS A 0 IN AN IF, SO THIS WILL EVALUATE TO FALSE (better to use ifdef)
#endif


can also do more crazy stuff like:

#if defined(DEBUG) && VERSION >= 3

**NOTE** there is a defined() pre-processor function!
CAN USE BOOLEAN ALGEBRA!


4. #ifdef
This is just #if defined()!

#ifdef DEBUG //will be true if defined
//stuff
#endif

**NOTE** 
aside from #define, can also do it directly in gcc
gcc -c -DDEBUG main.c -o main.o //HERE, -DDEBUG defines DEBUG

5. ifndef
//opposite, but very useful for header files to prevent you from including them too many times:

exe:
when you 
#include "file.h"

file.h:

#ifndef FILEH
#define FILEH
//code here for the header file:
int printz(char* str, int nums);
#endif

**NOTICE** THIS WAY, ONLY DEFINE TEH STUFF WHEN NOT PREVIOUSLY INCLUDED!!!
**KEY** WHEN YOU INCLUDE A HEADER FILE, WHAT THAT REALLY MEANS IS THAT IT JUST COPIES THE CODE FOR IT TO THE TOP
OF YOUR DOCUMENT, SINCE ITS KINDA LIKE A FUNCTION PROTOTYPE, BUT FOR EXTERNAL FUNCTIONS.


**NOTE** MODERN C PROJECTS CAN ALSO JUST USE PRAGMA:
#pragma once //enforces the added only once
#pragma pack(push,1) //uses 1 byte alighment (no spacing, best in certain cases)
#pragma pack(0)

exe:

struct bob {
    int a;
    char b;
}
#pragma pack(push,1) //bob will be 5 bytes, since uses 1 byte alignment
#pragma pack(0) //bob will be 8 bytes
#pragma pack(pop) //restores the previous packing order

6. #elif
exactly what you expect

7. #else









what to do to turn on / off different sections of code?:

#ifdef DEBUG
printf("stuff");
#else
print("Other stuff);
#endif

HERE: code will only execute if DEBUG is defined in the program
to define it:

either
#define DEBUG
or
-DDEBUG
(where -D flag for defining)

(NOTE: all of these are called pre-processor directives, ie the stuff with # since happens before compilation)

NOTE2: doesn't just have to be a print statment or a variable definition. can be entire functions

