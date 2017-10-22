#include "iostream"
#include "DynamicArray.h"

void Foo(const DynamicArray<int>);
int main()
{
    try{
    DynamicArray<int>a;
    
    std::cout << a.Capacity() << std::endl;
    std::cout << a.Size() << std::endl;
    
    a +=4;

    std::cout << a.Capacity() << std::endl;
    std::cout << (a+4).Capacity() << std::endl;
    std::cout << a.Capacity() << std::endl;
    
    std::cout << a[0] << std::endl;
    a[0] = 5;
    std::cout << a[0] << std::endl;
    //std::cout << a[20] << std::endl;

    const DynamicArray<int> b;
    std::cout << (b+4)[0] << std::endl;
    
    Foo(a);
    }
    catch(const char * const msg)
    {
        std::cout << msg << std::endl;
    }



    return 0;
}

void Foo(const DynamicArray<int> rhs)
{
    std::cout << rhs[0] << std::endl;
}