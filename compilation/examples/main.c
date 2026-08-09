#include <stdlib.h>
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

int main() {
    int x = 42;
    return 0;
}