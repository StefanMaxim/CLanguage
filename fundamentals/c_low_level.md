# Low Level Understanding: Bridging C's language level with how it actually works:

In a C program, there are 3 layers of "machines" involved with making a program:
1. The C Abstract Machine (the conceptual, abstract rules and conventions defined by the C language)
2. The Compiler's Internal Representation (where vars, types, expressions are represented mathematically)
3. The Real Machine (registers, addresses, bytes, instructions, immediates, virtual memory, processes, etc)

Compilers Job: Ensure that some sequence of operations in Machine 3 behave exactly as specified by Machine 1
(IT DOES PRESERVE C ABSTRACTION UNLESS ABSOLUTELY NECESSARY)

exe: given the source program:

```c
int main()
{
    int x = 42;
    return 0;
}
```
The final optimized version can be:

```assembly
xor eax, eax
ret
```

NOTICE: There is no X, no, int, no assignment, and not even a stack frame
(THOSE ARE CONCEPTS NEEDED FOR YOUR COMPILER TO UNDERSTAND YOUR PROGRAM, NOT THINGS THE CPU NEEDS TO EXECUTE IT)

## The fundamental C model: C describes behavior, not instructions
While people often think of C as "low level", it is still not low enough to where it describes actual instructions!
exe, when you write:

```c
int x = 42;
```

YOU ARE NOT SAYING:
> "Allocate four bytes on the stack and store the binary representation of 42 there."
(That may be what happens, but that is not what that line is saying)
Rather its:

> "Declare an **object** named x, having **type** int, automatic storage duration, and **initialize** its value to 42."

Terms Used:

Object = A region of data in memory whose contents can represent values
(different from Java/Python's definition of an object)
