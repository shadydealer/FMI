#include <stdio.h>

inline unsigned int first_missing(bool * arr, unsigned int len);

int main()
{
        unsigned int tomes = 0;
        unsigned int battles = 0;

        scanf("%u %u", &tomes, &battles);

        bool savedTomes[100000] = {false};

        unsigned int index = 0;
        unsigned int tomeIndex = 0;

        for (unsigned int i = 0; i < battles; ++i)
        {
                scanf("%u", &tomeIndex);
                savedTomes[tomeIndex-1]= true;
        }

        unsigned int missing= first_missing(savedTomes, tomes);
        
        if (missing== 0)
                printf("no\n");
        else
                printf("%u\n", missing);

        return 0;
}

inline unsigned int first_missing(bool * arr, unsigned int len)
{
    for(unsigned int i = 0; i < len; ++i)
        if(!arr[i])
            return i +1;
    
    return 0;
}
