#include <iostream>
#include "Queue-impl.h"

int main()
{
    Queue<int> q;

    for (size_t i = 0; i <= 10; ++i)
    {
        q.push(i);
    }
    std::cout << "------" << std::endl;
    
    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << q.pop() << std::endl;
    }

    std::cout << "------" << std::endl;
    std::cout << q.head() << std::endl;
    std::cout << "------" << std::endl;
    
    return 0;
}