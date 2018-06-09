#include <stdio.h>
#include "Polynomial.h"
#include <array>
void print_int_polynomial(Polynomial<int> &rhs);

int main()
{
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

    print_int_polynomial(a);
    printf("degree(a)=%u\n", (unsigned int)a);

    print_int_polynomial(b);
    printf("degree(b)=%u\n", (unsigned int)b);

    print_int_polynomial(c);
    printf("degree(c)=%u\n", (unsigned int)c);

    Pair<Polynomial<int>, Polynomial<int>> p = a / b;
    Polynomial<int> remainder = a % b;

    print_int_polynomial(p.first);
    printf("degree(quotient)=%u\n", (unsigned int)p.first);

    print_int_polynomial(p.second);
    printf("degree(remainder)=%u\n", (unsigned int)remainder);

    (--b)--;
    print_int_polynomial(b);
    ++((++b)++);
    print_int_polynomial(b);
    Polynomial<int> d;
    
    if(!d){
        printf("Yep yep\n");
    }
    printf("degree(b)=%u\n", (unsigned int)b);

    return 0;
}

void print_int_polynomial(Polynomial<int> &rhs)
{
    if ((unsigned int)rhs >= 0)
    {
        printf("(%d)*x^%d", rhs[0], 0);
        for (unsigned int i = 1; i <= ((unsigned int)rhs); ++i)
            printf(" + (%d)*x^%d", rhs[i], i);
        printf("\n");
    }
}