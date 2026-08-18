#include <stdlib.h>
#include <stdio.h>

typedef struct Person {
    char name[10];
    int age;

} Person;

int main() 
{
    Person p = {"Bob",4};
    printf("Name: %s\n",p.name);
    printf("Age: %d\n",p.age);
    printf("4th Character is: %c",p.name[3]);
    return 0;
}