#include <stdlib.h>
#include <stdio.h>


//CAN USE EITHER Person, or struct Person
typedef struct Person {
    char name[10];
    int age;

} Person;

int main() 
{
    Person p = {"Bob",4}; //NOTE: NOT A POINTER TO P, BUT REALLY P ITSELF!!
    printf("Size of p is %zu\n",sizeof(p)); //DOES NOT DECAY TO A PTR HERE!!! (format specifier)
    // THIS PRINTS 16!! NOT 14 (due to padding)

    Person arr[5];
    printf("Sizeof arr is: %zu\n",sizeof(arr));
    //THIS PRINTS 80, SINCE ITS LITERALLY AN ARRAY HERE!

    Person Person1 = arr[1]; //THIS IMPLICITLY YIELDS AN OBJECT (since type of left is also Person)
    Person Person2 = *(arr + 1);

    printf("Is Person1 the same as Person2: %d\n",Person1.age == Person2.age);
    //RETURNS 1, which is non-zero, so true


    printf("Name: %s\n",p.name);
    printf("Age: %d\n",p.age);
    printf("4th Character is: %c\n",p.name[3]);
    return 0;
}

/**
Note: When passing to functions however, must use types that are at most 8 bytes due to ABI calling convention, so it fits
In the register, also, can only return 8 bytes by convention as well, so to keep things easy, only return by referece


OKAY, BUT THEN WHY CAN LARGER TYPES LIKE struct Person EXIST, WHICH IS 16 BYTES???
ANSWER: An object in C is just a region in memory whose contents represent some value (or in this case struct with multiple
values). Thus as long as the compiler keeps track of 

1. The starting address of the struct
2. The offsets in the struct for its members
3. THe size of the struct

It can BEHAVE perfectly normally

*/
void printInfo(Person* dude)
{

}