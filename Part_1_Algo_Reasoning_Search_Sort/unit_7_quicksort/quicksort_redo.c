#include <stdlib.h>
#include <stdio.h>

//FUNCTION PROTOTYPE
int partition_array(int arr[], int lo, int pivot_index, int hi);
void quicksort_rec(int arr[], int lo, int hi);
void swap_int(int arr[], int init_idx, int final_idx);


int main()
{
    int arr[10] = {10,9,8,7,6,5,4,3,2,1};
    quicksort_rec(arr,0,10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}

/**
 * swap_int
 * 
 * swaps element at init_idx with the one at final_idx
 */
void swap_int(int arr[], int init_idx, int final_idx)
{
    int temp = arr[final_idx];
    arr[final_idx] = arr[init_idx];
    arr[init_idx] = temp;
}

/**
 * partition array: goal is, given a pivot index, to partition
 * array around that pivot, so all element before it are less
 * and all after are more
 * 
 * arr = array being partitioned
 * low = lowest index in the partitioned subarray, inclusie
 * hi = one above the largest index of the subarray being partitioned
 * pivot_index = index in the array from where to get the pivot
 * (can be chosen at random, but implemented to be middle element)
 * 
 * returns the pivot index
 */
int partition_array(int arr[], int lo, int pivot_index, int hi)
{
    //first, set up the array for partitioning by moving the pivot 
    //to the top

    swap_int(arr,pivot_index,lo);

    //save the pivot for easier comparison
    int pivot = arr[lo];

    /**
     * Termination Metric:
     * 
     * want all elements left in array, from lo+1 to hi-1 to be placed
     * tech: interate linearly through them. if less than pivot, move
     * to top of list, and if greater move to the end.
     * This way, naturally the final partitioned array will be 
     * 
     * pivot, less, less, less, ..., less, more, more, ..., more
     * 
     * just save the index of the last "less" before a "more"
     * 
     * swap the pivot back and call it a day.
     * 
     * scan is leftmost unsorted, right is rightmost unsorted idx+1
     * 
     * when there are n elements left, 
     * right - scan = n
     * for 1 element
     * right - scan = 1
     * for 0 elements:
     * right - scan = 0
     * 
     * thus, keep looping while right - scan > 0, or
     * scan < right
     * 
     */

    int scan = lo + 1;
    int right = hi; //again, will be one greater
    while(scan < right)
    {
        if (arr[scan] <= pivot)
        {
            scan++; //if leftmost unpartitioned is less, just move on
        }
        else
        {
            //else, means its actually greater
            swap_int(arr,scan,right-1);
            right--; //if greater, move to the back, now back not rightmost unsorted so move on

        }
    }
    //at the end of the loop, scan is one greater than leftmost
    
    int pivot_idx = scan - 1;
    swap_int(arr,lo,pivot_idx);
    return pivot_idx;
}


/**
 * Now, the recursive quicksort, which uses the helpers
 * partition_array, and swap_int
 * 
 * For recursion, recall rules:
 * 1. find base case P(0) equivalent
 * 
 * 2. split into subproblems
 * 
 * 
 * lo = leftmost index to sort
 * hi = one greater than rightmost index to sort
 */
void quicksort_rec(int arr[], int lo, int hi)
{
    //BASE CASE
    // if array is 0,1 or less elements, already sorted 
    // aka, if hi-lo <= 1
    if (hi - lo <= 1)
    {
        return; //0 or 1 already sorted, no prob
    }

    //NOW: find some random number to serve as the pivot:
    int pivot_idx = lo + (hi - lo) / 2;
    //Now, partition the array around that pivot:
    int final_pivot_idx = partition_array(arr,lo,pivot_idx,hi);

    //Now, lets work recursively on the sub arrays
    quicksort_rec(arr,lo,final_pivot_idx);
    quicksort_rec(arr,final_pivot_idx + 1, hi);
}
