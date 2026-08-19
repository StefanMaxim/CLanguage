#include <stdlib.h>

//FUNCTION PROTOTYPE:
int binary_search(const int arr[],int n, int x);

int main()
{

}

int binary_search(const int arr[], int n, int x)
{
    int lo = 0;
    int hi = n;

    while (lo < hi)
    {
        /**
         * Invariant:
         * 0 <= lo <= hi <= n
         */
        int mid = (lo + hi) / 2;

        if(arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] < x)
        {
            hi = mid;
        }
    }
}

lo = 2, hi = 5