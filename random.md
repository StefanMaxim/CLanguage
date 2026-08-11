# Random C Thing

## for loops
in C, structue of a for-loop is just initialization, condition, increment.
The initialization is anythign you want it to run once at the beginning. can be any valid c statment liek even a print
the condition just must yield some boolean-escque value. 

it can be:
1. a condition (a<b)
2. an integer
3. a double
4. a non-null ptr, like "hello", which in c is a char array char[]. decays to char*, so you can edit the string but 
its undefined, thus, better to use const char* to keep it constant.

The increment can again be any valid C statment

## bytes in c
char c = 12;
int a = 'a' what does it do?
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
NOTE: THIS IS BECAUSE THE POINTER SYMBOL IS THE WEAKEST, AND APPLIES LAST!!
```
Solution:
```c
(*)char[10] //NOW, this is a pointer to an array of characters!
```

pointer value is lvalue, pointer is rvalue.
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