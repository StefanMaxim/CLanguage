# Unit 7: Quicksort

Core Idea:
1. Divide
(choose a pivot, and partition the elements around it)

2. Conquer
Recursively sort the parts on either side of the pivot

3. Combine
Partitions already occupy correct locations in same array



First, choose some index p, so arr[p] serves as the pivot

Then, partition the array such that all the elements in indicies
lower than the pivot are less than the pivot, and above are greater
than the pivot

Idea here:First, temporarily move the pivot to the beginning

[(pivot)(<= pivot) ... (> pivot)]

scan = bound close to pivot, right = bound awa from pivot