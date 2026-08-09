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