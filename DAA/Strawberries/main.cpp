#include <stdio.h>

inline int binary_search( long *arr,int left,int right,  int el);

int main()
{
        int bowls = 0;
        scanf("%d", &bowls);

        int  strawberriesPerBowl[100000] = {0};

        for ( int i = 0; i < bowls; ++i)
            scanf("%d", &strawberriesPerBowl[i]);

        int tastyStrawberries = 0;
        scanf("%d", &tastyStrawberries);

        int currStrawberry = 0;
        long sum = 0;

        long sums[100000] = {0};

        for ( int i = 0; i < bowls; ++i)
        {
            sum += strawberriesPerBowl[i];
            sums[i] = sum;
        }

        int index = 0;

        for ( int i = 0; i < tastyStrawberries; ++i)
        {
                sum = 0;
                scanf("%u", &currStrawberry);
                index = binary_search(sums, 0, bowls, currStrawberry);
                printf("%u\n", index+1);
                
        }

        return 0;
}

inline int binary_search( long *arr, int left,int right,  int el)
{
    long middle  = 0;
    
    while(left <= right)
    {
        middle = (left+right)/2;

        if(el == arr[middle])
            return middle;
        
        else if(el > arr[middle])
            left = middle + 1;
        
        else 
            right = middle -1;
    }

    return left;
}



