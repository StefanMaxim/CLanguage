# Unit 1 Intro Notes (Algorithm Analysis)

## 1. Correctess + Invariants

### 1.1 Specification

**Specification**: What a function must do / what behavior is specified (rather than how it does it)

exe: for integer search
Input Array = a[0..n), target x
Output:
an index i st 0 <= i < n, and a[i] == x

Note: a[0..n) is notation for array indicies
a[0],a[1],a[2], ... , a[n-1] (INCLUDES 0, EXCLUDES N)

### Preconditions

**precondition**
describes states for which functions promises correct behavior
(what must be true before running the function to ensure correct behavior)

exe:
```c
int binary_search(const int a[], int n, int x)
// where a is an array, n is its size, x is the item to search for. returns index in array
//else sentinal value -1 for not in array
```

**KEY**
use **assert** in c to ensure compliance, but it is a runtime mechanism. 
```c
assert(n >= 0);
```

when rigorously analysing it, use "requires" to specify preconditions

### Postconditions
**postcondition** Describes the desired state when the function finishes, assuming pre-conditions 
are met. 
(what must be true when the function ends, given precondition)

exe: for int binary_search(const int arr[],int n, int x)

result is either -1 if element x not present in array, or index of element x in array, from 0 to n-1

result == -1 and x not present in arr OR
0 < result < n-1, and arr[result] == x

exe2: for sorting

a[lo...hi) is sorted

**KEY**
use **ensures** to specify post-condition



ALL TOGETHER:
a complete **specification** contains both a **precondition** and **postcondition**

exe: for int binary_search(const arr[], int n, int x)
for arr[0...n-1):

specification:
requires arr to be sorted, or for all i,j, i < j implies arr[i] < arr[j]
ensures arr contains same elements with same multiplicities (ie is a permutation of the initial)

### Assertions

**assertion** An explicit requirement that at this point is the program, something must be true


0,1,2,3,4,5

exe:
low = 0, high = n-1
```c
int mid = low + (high - low) / 2; //this is just low + high/2 - low/2 = (high + low) / 2
assert(lo <= mid && mid <= hi) //useful bc next line is likely arr[mid], so before access want to validate
```


### Loop Invariants
**Loop Invariant** a property that stays the same before and after a particular loop

exe:
```c
for (int i = 0; i < n; i++)
{
    ...
}
```

exe: **Bound Invariant** would be 0 <= i <= n

exe 2: Stronger Invariant for search:
Linear Search:
x does not belong in a[0..i)

### Loop Invariant Obligations

for invariant x is not in arr[0..i)

1. Initalization (show the invariant is true before the first iteration)

at i=0, arr[0..0) is empty, so it cannot be there

P(0)

2. Preservation (Assume true before iteration, show its true after executing the loop body)
(like proof by induction)


P(i-1) -> P(i)

3. Use at Termination
for i = n (or whenevr it terminats)

P(n)

together should imply postcondition. (same with proof by induction, thus must be true)

exe: if x is absent from arr[0...i), and i goes from 0 to n. then at nth iteration
x is absent from arr[0...n), which justifie returning -1
**NOTE** invariants must be strong enough to be useful, n >= 0 is a valid loop invariant, but
doesnt provide any useful info.

### Termination

Correctness also requires that the algo finishes, meaning you need some quantity that progresses to 
a stopping condition
**termination measure / variant** some quantity that progresses to a stopping condition

exe:
for (int i = 0; i < n; i++)

n-i is that value, which progresses towards 0

exe 2:
for searches
**hi - lo** is the termination measure, as it cannot be negative and every interation makes the 
interval smaller

### Partial vs Total Correctness

**Partial Correctness** if function terminates, its answer is correct
(differentn from Termination, whether a function actually terminates)

**Total Correctness**: When a function has both **partial correctness** and **termination**


### 1.9 Array Safety as part of correctness

exe: in binary search, not enough to just mathematically show answer is correct, but must also
show that no invalid memory accesses

in binary search
```c
int binary_search(const int arr[], int n, int x) //how is this valid? i thought will decay to ptr
```
this relies on 

int mid = (lo + hi) / 2;
arr[mid] //but cannot just assume its correct. 
must be certain that this array access is allowed (0 <= mid < n)

### Recursive Reasoning

given some recursive sort:
sort(a, lo, hi)

Base Case:
hi - lo <= 1 (if only 1 or fewer elements, its already sorted)

Recursive case:

1. Transform current problem into smaller subproblems
2. recursively solve them
3. use the recursive postconditions rather than mentally expanding the recursive calls


**CRUTIAL FOR WORKING THROUGH RECURSION**
exe: design a function for printing out n stars.
```c
void f(int n)
{
    ...
}
```
**Original Problem**: f(n) -> *****...* (n times)
**Sub-Problem**: consider case f(n-1), a subproblem is case:
****...* (n-1 times)

**connection** How to connect these ideas? first, do f(n-1), then
just print out another star.
void f(int n)
{
    f(n-1);
    printf("*");
}

**ISSUE: no termination condition**

```c
void f(int n)
{
    if (n == 0)
    {
        return;
    }
    else
    {
        f(n-1);
        printf("*");
        return;
    }
}
```


exe2: Factorials

**Problem** want to print out the n factorial
int factorial(int n)

**Sub-Problem** Given factorial(n-1), how to get to factorial(n)?

answer: first get f(n-1), then multiply by n to get f(n01)

**Base Case**
f(0) is just 1

```c
int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n-1);
    }

}
```

TIPS:

1. When in doubt, DRAW THE STACK! (lets you follow the steps)
2. State the full problem
3. Look for a subproblem (inductive step kinda)
4. Connect them


**OVERALL GUIDE**
(TREAT THIS LIKE HOW YOU TREAT PROOF BY INDUCTION)

1. Base Case. Find the solution to P(b)
2. Inductive Case (using either simple induction):
P(n-1) -> P(n)
Or strong induction:
[P(0), P(1), ..., P(n-1)] -> P(n)
3. Assemble the connection between them


### Data-Structure Invariants
**data-structure / representation invariant** Differetnt from loop invariant. Here, this refers to a property that a data-structure must maintain whenever it is considered valid.

exe: given a data structure for a sorted array
data-structure invariant:
elements[0...size) are sorted
0 <= size <= capacity





## Overall Correctness Template:

Specification: What a function does / what behavior is it expected to
have

Precondition: What properties must be true prior to the start of the function in order for it to have correct output. (requires:) (what state is required)

Post-condition: What properties must be true after the function is 
finished assuming that the pre-conditions were met

Invariant: (both loop / datastructure) A property that must be true
before the loop body at Initialization, Persistantly true, meaning assuming its true before the loop body, true after loop, and at termination must continue being true

Safety; Why every array access is valid

Progress: Termination metric / variant. some property that apporaches
a stopping value as the loop progresses.

Partially Correct = If function stops answer correct
Termination = the function does reach a terminal state
Totally correct = partially correct + termination

Postcondition: when termination is done, loop invarint should imply 
required result, like how in binary search, 
x is not in arr[0...i) implies that for i == n, will have reached
sentinal value.
