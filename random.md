# Random C Thing

## for loops
in C, structue of a for-loop is just initialization, condition, increment.

The initialization is anythign you want it to run once at the beginning, before the condition or loop body. can be any valid c statment like even a print (of course, it is indented to initialize your counter to 0 like for(x = 5;;), but in newer version of C you can also declare and define the variable there as well)

NOTE: IF the variable is declared in the loop, the variable's scope is that loop body. Once it leaves the loop, the variable goes out of scope and is removed. Else its where its declared


the condition just must yield some boolean-escque value. 

it can be:
1. a condition (a<b)
2. an integer
3. a double
4. a non-null ptr, like "hello", which in c is a char array char[]. decays to char*, so you can edit the string but 
its undefined, thus, better to use const char* to keep it constant.

The increment can again be any valid C statment

## bytes in c

int a = 'a' what does it do? //here, it ACTUALLY COMPILES, JUST THE ANSWER IS NOT WHAT YOU EXPECT
char c = 42; //likely will not work bc not compatible sizes (char = 1byte, int is 4 bytes)

The variable "a" shows up as 97 when printed as an int 
//NOTICE THIS IS THE ASCII VALUE OF A, so it likely wrote the integer 97 (implicit typecast)


The variable "a" shows up as a when printed as an char (The )

The variable "c" shows up as 42 when printed as an int
The variable "c" shows up as * when printed as an char

DOES %c only print the first byte, or the whole thing (meaning all 4 bytes, then converts to ascii?)



int* = 

given some:
typedef struct Person {
    char* name;
    int age;
} Person;

what is 

Person* p;, and can you set that equal to what?





## types, like long

integer types, their size, their format specifier
size_t = unsigned long int?
long is a type specifier, meaning it is used in tandem with a fundamental type to specify behavior
long on itself in reality becomes long int
long = guarentees at least 32 bits, 
long long = guarentees at LEAST 64 bits

void
char
short
int
long
signed
unsigned
_Bool      // C99

int = signed = signed int




## format specifiers
width, precision, type or something
min width, precision = number of digits after the decimal
"-" means left justifier
0 means pad the width with 0s, (decimals automatically padded with 0s) (REVIEW)

## Pointers
position of the "*" matters!
pointer to an array of chars vs an array of char pointers
```c
*char[10] //KEY: by default, this is an array of char pointers, NOT A POINTER TO A CHAR ARRAY!
NOTE: THIS IS BECAUSE THE POINTER SYMBOL IS THE WEAKEST, AND APPLIES LAST!! **(REWRITE)**
```
Solution:
```c
(*)char[10] //NOW, this is a pointer to an array of characters!
```

pointer variable is lvalue, pointer is rvalue.
lvalue is assigned an rvalue, and lvalues decay to rvalue when used in assignment.

KEY: In the AST(look at the notes) an l-value yields an address, and an r-value yields a value;

exe:
int x = 4; 
here, x is the l-value and 4 is the rvalue.

x is a integer object in memory, and 4 is a constant,
the constant variable will yield the value "4", and the identifier of x will yield the address of the 
integer object that it represents. From there, you just write the value to the address.
That is key to understanding how C works


when you assign a pointer to something or really anything to anything else, you are just writing new data to its
area in memory:
int x = 4; you are just writing 4 at the memory address of x.

same for ptrs, 

## single vs double quotes in c

## Assignment:

## struct
can store flags, less that single byte (REVIEW)
stuct obj{
    flag : 1
};

Also: CAN DECLARE + DEFINE + INITIALIZE STRUCTS LIKE:
Person p = {"Bob",4}; //NULL TERMINATED

## Arrays
Array vs Pointer, since arrays are one of the few types that exist out of the standard primitive objects
and pointer objects via structs

also, given a char** array, you can still use array indexing arr[2][3] despite not being type array?

ALSO: ITS TYPE IDENTIFIER, THEN ARRAY NOTATION
int nums[10];

**KEY IDEA** just like how you can have a struct without needing a pointer to it, you can do the same with arrays
Person p; //just initialized to garbage, but THERE IS A WAY TO INITIALIZE THE STRUCT
int[5] a;

typedef struct Person 
    {
        char name[10];
        int age;
    } Person;

you can just create Person p;, which creates a Person object in memory, not initializing it (just claiming the memory on
the stack)

But, if you try to edit it via:
p.name = "Ben" WILL ERROR: p MUST BE A MODIFIABLE LVALUE. (it is an l-lvaue but not modifiable, read AST FOR THIS)
(arrays are "immutable", in that you cannot change their underlying pointer, only their contents:

p.name[4] = 'b'; is a-okay

)
p.age = 12; is a-okay tho.

## Environment
sudo apt install build-essential gdb valgrind pkg-config manpages-dev

build-essentials just has a bunch of useful executables like gcc and libc, very useful
gdb is gnu debugger, good for debugging c code
valgrind is for memory checks, makes sure no memory leaks (allocate memory, but never free it) (remember to compile in debug mode)

## Big Picture:

int x = 42;

object = In C, an object is a region of memory that represents 
a value

value = an abstract idea, exe: the number 1, specifically the idea 
of "1". (material vs spirit metaphysical stuff)

expression: ways to represent the idea of something:
exe: "1" this symbol is an expression of the idea of 1, so it
"one" or 2-1, or any other symbols we interpret as representatives of
the abstract idea

identifier: the name x, which can be used to reference the object in 
memory. 

type: "int" in this case, which defines the set of values that are
acceptable as values, as well as other general compiler-side 
metadata like size, interpretation, etc

int is the type, which is a class/set of values, but also defines
things like the size of the obect