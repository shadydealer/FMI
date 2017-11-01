#include <iostream>

int main()
{
    bool isLessThan = true, isGreaterThan = true;
    int currNum = 0, prevNum = 0, lines = 0;
    std::cin >> lines;

    for (size_t i = 0; i < lines; ++i)
    {
        std::cin >> currNum;
        if (i)
        {
            if (i == 1)
            {
                currNum < prevNum ? isLessThan = false : isGreaterThan = false;
            }
            else
            {
                if (isGreaterThan)
                {
                    isGreaterThan = false;
                    if (currNum > prevNum)
                    {
                        isLessThan = true;
                    }
                }
                else
                {
                    if (isLessThan)
                    {
                        isLessThan = false;
                        if (currNum < prevNum)
                        {
                            isGreaterThan = true;
                        }
                    }
                }
            }
            if (currNum == prevNum)
            {
                isGreaterThan = true;
                isLessThan = true;
            }
        }
        prevNum = currNum;
    }

    std::cout << ((isLessThan || isGreaterThan) ? "yes\n" : "no\n");
    return 0;
}