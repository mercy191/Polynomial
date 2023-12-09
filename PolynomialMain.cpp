#include <iostream>
#include "Polynomial.h"

int main()
{
    Polynomial poly1;
    Polynomial poly2;
    Polynomial poly = poly1 + poly2;
    std::cout << poly << '\n';
    poly1 /= 2;
    std::cout << poly1 << '\n';
}

