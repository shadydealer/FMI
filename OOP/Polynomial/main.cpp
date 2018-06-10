#include <stdio.h>
#include "Polynomial.h"
#include <array>

int main()
{
    Polynomial<int> inputPol;
    std::cin >> inputPol;

    std::cout << inputPol;
    
    Polynomial<int> a;
    a.set_at(3, 1);
    a.set_at(2, -2);
    a.set_at(0, -4);

    Polynomial<int> b;
    b.set_at(1, 1);
    b.set_at(0, -3);
    int point = 4;

    int lower = 1;
    int upper = 5;

    printf("definite integral of b in [%d;%d] = %d\n", lower, upper, b(lower, upper));

    printf("b at %d = %d\n", point, b(point));
    Polynomial<int> c = a + b;

    std::cout << a;
    printf("degree(a)=%u\n", (unsigned int)a);

    std::cout << b;
    printf("degree(b)=%u\n", (unsigned int)b);

    std::cout << c;
    printf("degree(c)=%u\n", (unsigned int)c);

    Pair<Polynomial<int>, Polynomial<int>> p = a / b;
    Polynomial<int> remainder = a % b;

    std::cout << p.first;
    printf("degree(quotient)=%u\n", (unsigned int)p.first);

    std::cout << p.second;
    printf("degree(remainder)=%u\n", (unsigned int)remainder);

    (--b)--;
    std::cout << b;
    ++((++b)++);
    std::cout << b;
    Polynomial<int> d;
    
    if(!d){
        std::cout << "Yep yep\n";
    }
    printf("degree(b)=%u\n", (unsigned int)b);

    return 0;
}
