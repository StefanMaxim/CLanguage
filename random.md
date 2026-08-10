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

when you assign a pointer to something or really anything to anything else, you are just writing new data to its
area in memory:
int x = 4; you are just writing 4 at the memory address of x.

same for ptrs, 

## single vs double quotes in c