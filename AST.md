# Low Level Understanding: Bridging C's language level with how it actually works:

KEY IDEA: A C PROGRAM IS NOT A LIST OF INSTRUCTIONS FOR THE CPU, BUT RATHER A DESCRIPTION OF A PROGRAM IN THE C LANGUAGE.

In a C program, there are 3 layers of "machines" involved with making a program:
1. The C Abstract Machine (the conceptual, abstract rules and conventions defined by the C language)
2. The Compiler's Internal Representation (where vars, types, expressions are represented mathematically)
3. The Real Machine (registers, addresses, bytes, instructions, immediates, virtual memory, processes, etc)

Compilers Job: Ensure that some sequence of operations in Machine 3 behave exactly as specified by Machine 1
(IT DOES PRESERVE C ABSTRACTION UNLESS ABSOLUTELY NECESSARY)


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

exe:
```c
int x = 42;
```

**Syntax** means "Is this code gramatically correct / What gramatical construct is this?"
It does not care what this statment means, (with regard to syntax, its all just symbols), but based on the pattern of the
symbols, it can tell this is a **declaration with an initializer**

**Semantics** means "What does this mean / what does that declaration mean"
Roughly:
"Declare an object named x, whose type is int, and initialize that object with teh value obtained from the expression 42"

I used some words there which are useful to know:

**Value** is an abstract piece of information belonging to a type
exe:
42
3.14
'a'
NULL pointer value

Notice, it is NOT the 42 in "int x = 42", that 42 is an expression. The 42 I mean is the abstract idea representing 42,
which has many different representations as expressions:
42
forty-two
4*10 + 2
6*7
etc...

**Expression**
An expression is a piece of C syntax that specifies some computation or designation:
exe:
42
x
x+1
*p
&p
a[i]
foo()
x = 5

These expressions are not values on their own, but **yield values** when computed

Expression have
1. A type (like above with "declaration with an initializer")
2. semantic properties
3. potentially a resulting value
4. potential side-effects (unless it is a functional programming language)



**Type**
A type tells C what kind