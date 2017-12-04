#include "iostream"
#include "cstring"

void gravity_sort(int *rhs, int size);

int main()
{

    return 0;
}

//
//  Gravity Sort, a.k.a Bead Sort.
// Works only with positive integers.
//
//  Time Complexity:
// Worst case : O(S), where S is the sum of the input integers.
//
//  Memory Complexity:
// O(N^2) where N is the count of the integers in our array.
//
//  What it does:
// Suppose we have an array [2,5,3].
//
// We then alocate a 2D array[N][Max], where Max is the largest integer in the array.
// Now we distribute as many "beads" on each column of the array starting from the top,
// as the size of the number. For example:
// we would have "beads" in array[0][0] and array[0][1] positions for the first integer in our array.
// The same follows for the rest of our integers.
//
// Now that we've disstributed the "beads" we have to let them "fall" into place, as if we had an abacus.
// Example:
//
//  step 1: Distributing the "beads".
//  1   1   0   0   0
//  1   1   1   1   1
//  1   1   1   0   0
//
// where 1 = bead & 0 = empty.
//
//  step 2: Sorting the "beads".
//  1   1   0   0   0
//  1   1   1   0   0
//  1   1   1   1   1
//
//  The "beads" "fall" to a lower lever if there is no "bead" beneath them.
// Now the integers are sorted
// and all taht's left is to set them into their correct positions in the array.
//
void gravity_sort(int *rhs, int size)
{
    unsigned int max = 0; // for the maximum integer in the array.

    //
    //finds the max integer.
    // O(n).
    //

    for (int i = 0; i < size; ++i)
    {
        if (max < rhs[i])
            max = rhs[i];
    }

    std::cout << max << std::endl;

    bool *temp = new bool[size * max];

    //
    //  O(n).
    //
    memset(temp, 0, size * max);

    int index = 0;

    //
    //  Distributes the beads onto the "poles"
    //  approx. O(S)
    //
    for (int i = 0; i < size; ++i)
    {
        index = i * max;
        for (int j = 0; j < rhs[i]; ++j)
        {
            temp[index] = 1;
            //std::cout << index << " ";
            ++index;
        }
        //std::cout << std::endl;

        index = 0;
    }

    int sum = 0;

    //
    // approx. O(n*S)
    //
    for (int i = 0; i < max; ++i)
    {

        //sum all the ones on each "pole".
        for (int j = 0; j < size; ++j)
        {
            sum += temp[i + j * max];
            temp[i + j * max] = 0;
        }

        //std::cout << "sum: " << sum << std::endl;
        //"beads" "fall" into place.
        for (int j = size - sum; j < size; ++j)
        {
            temp[i + j * max] = 1;
            //std::cout << temp[i + j * max] << " ";
        }
        //std::cout << std::endl;

        sum = 0;
    }

    rhs[0] = max;

    for (int i = size - 2; i >= 0; --i)
    {
        for (int j = 0; j < max && temp[i * max + j]; ++j)
            ++sum;

        //std::cout << sum << " ";
        rhs[size - i - 1] = sum;
        sum = 0;
    }
    //std::cout << std::endl;

    delete[] temp;
}