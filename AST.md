# Low Level Understanding: Bridging C's language level with how it actually works:

KEY IDEA: A C PROGRAM IS NOT A LIST OF INSTRUCTIONS FOR THE CPU, BUT RATHER A DESCRIPTION OF A PROGRAM IN THE C LANGUAGE

The compiler first figures out what the program means according to C's rules, and then only afterwards chooses the assembly
code that produces the desired result.

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

**NOTICE**: There is no X, no, int, no assignment, and not even a stack frame
(THOSE ARE CONCEPTS NEEDED FOR YOUR COMPILER TO UNDERSTAND YOUR PROGRAM, NOT THINGS THE CPU NEEDS TO EXECUTE IT)

exe 2:
given again the same code snippet:
```c
int x = 42
```

YOU ARE NOT SAYING:
> "Allocate four bytes on the stack and store the binary representation of 42 there."
(That may be what happens, but that is not what that line is saying)
Rather its:

> "Declare an **object** named x, having **type** int, automatic storage duration, and **initialize** its value to 42."



There are many stages that your source goes through to gain meaning and transition to assembly:
source text
    ↓
tokens / grammar
    ↓
C semantic meaning
    ↓
AST
    ↓
compiler IR
    ↓
optimized IR
    ↓
machine-specific operations
    ↓
assembly
    ↓
machine code

## Term Understanding:

### Syntax vs Semantics