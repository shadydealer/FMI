#include <stdio.h>
#include "Dynamic_Array.h"
#include "Wallet.h"

int main()
{
    try
    {
        Dynamic_Array<Wallet> arr;
        for (unsigned int i = 0; i < 10; ++i)
        {
            Wallet temp(i, "J");
            arr.push_back(temp);
        }

        for (unsigned int i = 0; i < arr.get_size(); ++i)
        {
            printf("id: %u, balance: %f, name: %s \n", arr[i].get_id(),
                                                       arr[i].get_money(),
                                                       arr[i].get_owner());
        }
    }
    catch (std::bad_alloc())
    {
    }
    return 0;
}