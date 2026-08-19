# Unit 8: Merge Sort

Loose Idea:

Same divide and conquer idea as with quicksort, only different in recursive calls.

given arr[lo...hi)

1. first, split the array in half:

int mid = (lo + hi) / 2; //some middle index

this yields 2 arrays
arr[lo...mid)
arr[mid..hi)

2. Then, sort the 2 subarrays

creating 

arr1[lo,mid) sorted, and arr2[mid,hi) sorted.


3. Lastly, merge the two sorted arrays into a single sorted array:

exe:

arr1: [2,5,8]
arr2: [1,3,7]

to make a full array, arr3, compare the first elements of arr1 and arr2

2 vs 1, is smaller, so append to big:

arr3: {1,}

and remaining is
arr1 = [2,5,8]
arr2 = [3,7]

NOW: 2 vs 3
2 is smaller, add and remove from arr 2

arr3 = [1,2]
arr2 = [5,8]
arr1 = [3,7]

etc

## Merge Pointers:
How to implement this: use pointers:

left_idx = current position in left range
right_idx = current position in right range
merged_idx = next position in temporary output

Initally:
left_idx = lo
right_idx = mid
merged_idx = lo (NOTE: will likely have to dynamically create a new array to store the temp data)

