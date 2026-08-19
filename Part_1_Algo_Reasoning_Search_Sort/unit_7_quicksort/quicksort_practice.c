//FUNCTION PROTOTYPES


int main()
{

}

// lo starts at 0, hi starts at n
//The goal of this is purely to sort so all before are below, rest are above
static int partition_range(int arr[], int lo, int pivot_index,int hi)
{
    int pivot = arr[pivot_index]; // find the pivot
    swap_int(arr,lo,pivot_index); //puts the pivot at the top of the array

    int scan = lo + 1; //one before pivot
    int right = hi;

    //invariant
    while (scan < right)
    {


        /**
         * in the array, the first element, at lo is the pivot
         * the second is scan (first unsure element)
         * and right is the rightmost element, hi (size of array)
         * [lo...hi)
         * 
         * idea is again: close to pivot = less, 
         * far from pivot = greater
         * 
         * This way, scan stays leftmore uncertain
         * and right - 1 is rightmost uncertain.
         * 
         * keep determining them untill
         * no more uncertain elements, 
         * 
         * scan keeps increasing, right keeps decreasing
         * 1 elements when scan == right - 1
         * 0 elements (terminate when) scan > right - 1
         * 
         * Thus, the termination metric is high-low (with 0 being stopping condition)
         * 
         * so while loop is while while high-low > 0
         * or low < high
         * 
         */

        if(arr[scan] <= pivot)
        {
            scan++;
        }
        else
        {
            swap_int(arr,scan,right - 1);
            right--;
        }
    }
    //at termination: scan is one creater than the last digit moved
    //thus, swap with scan - 1 since pivot index is less, adn scan-1
    //also less

    int final_pivot = scan - 1;
    swap_int(arr,lo,final_pivot);

}




/**
 * Now that partition is done, the actual quicksorting isnt bad
 * 
 * lo = 0 at first, hi = num elements
 */
static void quicksort_rec(int arr[],int lo, int hi)
{
    //BASE CASE: 0 or 1 elements sorted
    //in other words hi-lo <= 1
    if (hi - lo <= 1)
    {
        return;
    }
    else
    {
        //for choosing pivot, just pick a random one for now, middle
        // 0,1,2,3,4 (lo=0,hi=5)
        int pivot_index = (lo + hi) / 2;
        int p = partition_range(arr,lo,pivot_index,hi); //partitioned
        quicksort_rec(arr, lo, p); //its p, since high is one over
        quicksort_rec(arr, p + 1, hi); // p+1 bc p not necessary to check

        //KEY: pivot_index is just randomly the middle one
        //but after partitioned, it is not necessarily in the middle of
        // the array


    }


}