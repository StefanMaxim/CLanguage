# Unit 5: Binary Search

## Preconditions:

requires:
1. arr[lo...hi) is sorted increasing

## Main Idea

keep some interval [lo,hi)
where 
lo = 0, hi = n

at every step, look at mid:

int mid = (lo + hi) / 2;

arr[mid], 3 cases:

1. if arr[mid] is x, return mid,
2. if x is less than arr[mid], then search on subinterval
(0,mid-1)
3. If x is greater than arr[mid], search on subinterval (mid+1,hi)

Termination Condition:
(the termination measure is hi-lo, which approaches 0)
thus, must check lo < hi

