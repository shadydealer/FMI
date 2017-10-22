#include <iostream>
#include "Tab.h"
#include "Browser.h"

void RunTests();

int main()
{
    RunTests();
    std::cout << " hello world" << std::endl;
    return 0;
}

void RunTests()
{
    Tab a;
    std::cout << a.url() << std::endl;
    std::cout << a.timeStamp() << std::endl;

    std::cin.ignore();
    
    Tab b("tits.com");

    std::cout << b.url() << std::endl;
    std::cout << b.timeStamp() << std::endl;

    Tab c(b);


    std::cout << c.url() << std::endl;
    std::cout << c.timeStamp() << std::endl;


    Browser br;
    std::cout << (br.data()[0])->url() << std::endl;
}
