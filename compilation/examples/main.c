#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

//generally define your structs outside of main, unless you want its scope to be only inside of main

struct Person
{
    char* name;
    int age;
};

typedef struct
{
    char* name;
    int age;
} Person;

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

//KEY DIFFERENCE:
/**
 * the first one, which uses struct Person creates a struct with the tag "struct Person"
 * 
 * when creating objects with it, its "struct Bob person;""
 * 
 * the second one does 2 things:
 * 1: creates an anonymous struct:the struct{} part, which means it has no tag
 * 2: then, typedef's it to Person
 * (you can use typedef by itself, like: "typedef int billy;" which means typing billy is the same as typing int)
 * NOTE: DIFFERENCE BETWEEN #define MyInt int and typedef int MyInt;
 * #define is pre-processor tag, not visible to compliler
 * typedef just defines a new name for an existing type (visible to the compiler) typedef int MyInt
 * HOWEVER: when defining structs, struct Person {}, you need to define the full word "struct Person"
 * because it needs the struct namespace. CANNOT USE THE ALIAS BC IT DOESNT EXIST YET THERE.
 * 
 * KEY: useful for self-reference:
 * typedef struct Node {
 *     int value;
 *     struct Node *next; //works bc this is just a pointer, so a constant 8 bytes (cannot type Node here bc 
 *      typedef doesnt exist yet)
 *  } Node;
 * 
 * NOTE: recall, typing struct Bob person; just declares + defines it (meaning it declares to the compiler that it
 *       exists and initializes the space for it in the stack, just like it would for an int)
 * The struct exists, but has garbage there untill you initialize it to somethign useful
 */
/**
 * main.i is massive, main.c is small
 * #include is a pre-processor macro, which just shoves the code for that library (its header file, to be precise)
 * into the code.
 * 
 * thus, including stdio.h copies its header file there, but it itself depends on other things, like types
 * being defined. thus, it creates a massive chain of imports:
 * main.c
 ├── stdio.h
 │    ├── stddef-related definitions
 │    ├── system type definitions
 │    └── compiler/platform headers
 │
 ├── stdlib.h
 │    ├── size types
 │    ├── integer types
 │    └── system headers
 │
 └── unistd.h
      ├── POSIX types
      ├── system definitions
      └── architecture-specific headers


 * KEY: notice also, that the assembly is very small.
 * this is because all these function prototypes, and even the struct definitions are for the compiler ONLY
 * THey jsut tell the compiler what to expect, what types of functions exist, and what the types are
 * In the final assembly code, that stuff is not necessary, neither the prototypes nor the struct defs
 * 
 * The structs are just like the types: in the final code its just addresses and registers, no types.
 * 
 * 
 */

//FUNCTION PROTOTYPES:
Person* create_person(const char* name,int age);
void destroy_person(Person* person);
void print_info(Person* person);



int main() {
    int x = 42;
    Person* person = create_person("Bob",12);
    print_info(person);
    destroy_person(person);
    return 0;
}

/**
 * creates a person, given a string (which in c is really just a char[], not even const, but is good to be const)
 * and an int age
 * 
 *  Person *create_person(const char* name,int age)
 */
Person* create_person(const char* person, int age)
{
    Person* p = (Person*) malloc(sizeof(Person)); //just malloc'ed space for the full struct, declared+defined a poitner to that struct
    //and set its value to the address of malloc, using type conversion bc by default is void*
    if (p == NULL || person == NULL) //must check for null, unlike python which just passes the Null equivalent when no args
    {
        return NULL;
    }
    //NOTE: cannot just "p->name = person", because person is a pointer variable, unless you want it to write that value, 
    // which will error anyways. p->name here becomes an lvalue, representing the name attribute of the p object
    //that exists in memory (rather the space in memory). Thus, it can be re-assigned no problem because its not const,
    //but thats not what you want, since if you just set it equal to that "person" it will point to the string, not a new
    //object like you want

    //Thus, you need to copy that string (carefully, since person may be a malformed string with no \n, and strcpy)
    // will copy untill it reaches a \n, which could error. 
    p->name = strdup(person);

    //this method creates a new string, copies the string from the pointer value, and then assigns it to the pointer variable
    //thus, must check if its not null:
    if (p->name == NULL)
    {
        free(p);
        return NULL;
    }
    p->age = age;
    return p;
}

void destroy_person(Person* person)
{
    if (person == NULL)
    {
        return;
    }
    if (person->name == NULL)
    {
        free(person); //if name is NULL, it means that there is no other remaining malloc'ed space, thus, you can 
        //just free the struct because everything else, like the int and the ptr are inside of the struct, so free
        //removes the last 8+4 bytes, returning all memory
        return;
    }
    else
    {
        free(person->name);
        free(person);
        return;
    }
}

void print_info(Person* person)
{
    if (person == NULL)
    {
        return;
    }
    else if (person->name == NULL)
    {
        printf("Malformed Person: no name");
        return;
    }
    else
    {
        printf("Hello!\nMy name is %s and I am %d years old.",person->name,person->age);
        return;
    }
    
}