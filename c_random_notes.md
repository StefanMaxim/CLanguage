### Memory as bytes:
Every running process has a virtual memory space (read up on processes to get the gist). Conceptually, it resembles a large array of bytes:

Address        Contents
0x1000         01101010 
0x1001         00000001
0x1002         11100010
...

Of course, it is more complicated than that, but the CPU in reality mostly just reads bytes from this array,
loads them into registers (small, fast units of memory closer to the cpu), operates on them (and stores the result in some other register), and then writes it back to memory

The CPU does NOT know what these bytes represent, be them:
an integer,
a string,
a Person,
a Python class,
a function,
or a list.

**KEY** Those meanings come from conventions made by the programming language, the compiler, or the runtime(the piece of software responsible for running the code, handling the memory, and other runtime tasks)

#### C Pipeline Brief:
>EXE: 
In C, suppose you write:

```c
int main() {
    int x = 42;
    return 0;
}

```
1. At first, this command is just characters on disk (can see by opening file with Hex Editor in VSCODE):
i n t  x  =  4 2 ;

2. Compiler processes it, and understands:
- create a variable named x
- its type is int
- initialize it with value 42
This information is then stored in the compiler 

3. Compiler generates the assembly code(opcode) representing that line
on 64 bit x86, might look something like: mov DWORD , 42
(use gcc -S main.c -o main.s t see it)

```assembly
mov DWORD PTR [rbp-4], 42
```
Breakdown:
    mov (overloaded command, used to move things from place to another, be it from memory to register, register to register,
    or literal to register)

    - DWORD is the size/amount of bytes to move (BYTE = 1 byte, WORD = 2 bytes, DWORD = 4 bytes, QWORD = 8 bytes)

    - PTR is pointer, it tells the assembler that the thing inside the [] is a memory address

    - [rbp-4] = address of the Register Base Pointer minus 4 (look at stack notes to understand why) (loosely, new function means new stack frame, and the first thing you do it push the current rbp on the stack (representing the address where the previous rbp is stored in the above stack). 
    Thus, you decriment RSP by 8, then write RBP to RSP (will print up, since writing at 0x1000, writes 0x1000 to 0x1007)
    Lastly, you set the RBP to the Current RSP, which is conveniently at the place in memory where the previous
    rbp was written.


    Then, rsp moves down to create new variables. Thus, the value in the RBP functions like the "top" of the function, since
    above it is the 8 bytes for the address of the previous rbp, and then the above that is the previous calling function's
    stack frame. Thus, you -4 from the rbp (which equals the rsp) to allocate 4 bytes for the int, and then print it there.
    (confusing, i know, just read the stack notes)

    - 42 the immediate (constant) to write 

**NOTICE** there is no "x" in this command! X only exists for debugging purposes. Its now all just memory and addresses!
C source
   │
   │  "x is an int called x"
   ▼
AST
   │
   │  "x is local variable #17"
   ▼
Intermediate Representation (IR)
   │
   │  "this value lives in stack slot 3"
   ▼
Machine-level representation
   │
   │  "[rbp-4]"
   ▼
Assembly
   │
   │  "memory address"
   ▼
Machine code
   │
   │  "bytes: 89 45 FC ..."
   ▼
CPU

4. Assembler converts the assembly code into bytes (machine code)

exe: C7 45 FC 2A 00 00 00 (last 4 bytes are the number in binary, little endian)
(**NOTE**: doesnt necessarily write one byte at a time, harware just writes the whole thing, with 2A going to lowest address and working its way up from there.):
write 0x12345678 to 0x1000:
conceptually, 0x1000 gets LSB (78), then 0x1001 get next lbs (56) etc up to 0x103 (SO YES IT STARTS LOW, AND WORKS ITS WAY
TO HIGHER ADDRESSES)

And the resulting bytes are stored in some executable file (like the linux ELF, read about that). which also contains:
- machine code
- constants
- symbols
- debug info

5. You run the program:

./myprogram

OS creates a new process + virtual memory space according to the loader and the executable:
+--------------------+ 0x00000
| Code (.text)       |
+--------------------+
| Globals (.data)    |
+--------------------+
| Heap               |
|                    |
|                    |
+--------------------+
|                    |
| Stack              |
| grows downward     |
|   (low addresses)  |
+--------------------+ 0xFFFFF

6. CPU begins execution of the instructions
Its instructions are found in the Code (.text) section, and goes one by one, untill it reaches:
mov DWORD PTR [rbp-4], 42

Suppose RBP = 0x7fffffffe000
RBP-4 => 0x7fffffffdffc
(RECALL: RBP is a pointer to the top of the stack, which happens to house the address of the previous stack frames rbp)
(this creates a linked list of stacks that are critical for debugging)
however, the address itself can be thought as the top of the function (look at stack notes)

Thus, the instruction means "memory at 0x7fffffffdffc = 42"

7. CPU executes instruction:

> Fetch:

Instruction fetched into instruction cache from memory

C7 45 FC 2A 00 00 00
        ↓
CPU

> Decode:
CPU realizes it must

Operation:
Store 32-bit immediate

Destination:
RBP - 4

Value:
42

> Execute
CPU computes: address = RBP - 4
0x7fffffffe000
-          0x4
----------------
0x7fffffffdffc

> Write
CPU sends to memory bus:

Address = 0x7fffffffdffc

Data = 42

Cache recieves the write, propagates to memory if necessary

8. What was stored:

42 as hex is: 0x2A
and in binary is: 00101010

as a 32 bit integer:
00000000
00000000
00000000
00101010 (using normal notation)

However, on a CPU that uses little endian (least significant bit in low addresses):

Address          Value

0x...ffc         2A (low)
0x...ffd         00
0x...ffe         00
0x...fff         00 (high)

9. Later, when accessing x, exe:
printf("%d\n", x);

compiler generates the assembly:
mov eax, DWORD PTR [rbp-4] **NOTICE: ONLY THE COMPILER KNOWS WHAT "X" MEANS, OTHERWISE IT DOESNT EXIST**
and the stuff is repeated


The compiler knows that that specific memory address / CPU register can be interpreted as an int (by reading it, and the)
and then generates instructions that treat those bits as an integer.

### Back to Memory as bytes

#### Structs

suppose you have 

struct Person {
    char* name; //**NOTE** CAN be an array, just specify size char[50] name (but this way not dynamic and can waste space)
    //thus, better to use a dynamic string
    int age;
}
or
typedef struct {
    char* name;
    int age;
} Person;

Here, you created a new struct, with the tag "struct Person" in the struct namespace
the anonymous struct, now aliased to "Person" now establishes the layout:
Beginning of Person
        │
        ▼
┌────────────────────┐
│ pointer to name    │
├────────────────────┤
│ integer age        │
├────────────────────┤
│ possible padding   │
└────────────────────┘ //padding bc C often likes to use 8-byte alignment. Useful for address math + SIMD if needed

if 
Person *p; (this declares + defined a variable of type Person Pointer, size 8 bytes)
p->age will use the compiler's known offset of age, and add that to the address stored in p.(NOTE: assuming allocated
the Person object, as right now its just as a pointer)
**NOTICE** the bytes do not identify themselves as a Person. It just behaves like it because program follows layout and
lifetime rules associated with that struct.



#### Malloc
Malloc itself does not create OOP objects!

to allocate space for the object in C:

**OBJECTS IN C**
Object = region in memory that can represent values
(when you int x = 42; there is an int object associated with x created in memory that represents the integer 42)

Value = abstract concept, representing the idea that the object represents

Type = describes the set of values that an object can have and its size in memory

Ientifier = the literal "x" used to refer to the object

struct Person *p = malloc(sizeof(struct Person));

**SIZEOF**
one of few functions that do not decay arrays and other objects to pointers
sizeof(variable)
sizeof(type) (returns size_t, aka unsigned int so use %zu to display)
remember to dereference the pointer to see the size of the thing it references

malloc takes in a number of bytes, and returns an address representing the start of the allocated memory in the heap.
**KEY**
HOWEVER, THAT MEMORY IS JUST ALLOCATED! IT IS GUARENTEED TO BE FREE AND NOT EAT INTO SOMETHING THAT EXISTS.
That being said, there is no name string and age that exists there yet. you have to initialize it via:

```c
struct Person *person_create(const char *name, int age) {
    struct Person *p = malloc(sizeof *p);

    if (p == NULL) {
        return NULL;
    }

    p->name = strdup(name); //here, the left is a pointer to a char, same as (*p).name

    if (p->name == NULL) {
        free(p);
        return NULL;
    }

    p->age = age; //left is an integer
    return p;
}
```
and eventually disband them via:

```c
void person_destroy(struct Person *p) {
    if (p == NULL) {
        return;
    }

    free(p->name); 
    free(p); //dont have to free the int bc its inside of the struct, the string however can be somewhere else, pointed
    //to by the pointer char *name, which can be in a different place
}
```

Thus, there are several key ideas at play here:

1. Allocation:
Obtain raw storage.

2. Initialization:
Put the storage into a valid starting state.

3. Use:
Operate on the valid representation.

4. Finalization:
Release resources owned by the value.

5. Deallocation:
Return its storage to an allocator.


