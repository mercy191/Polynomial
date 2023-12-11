#include <iostream>
#include "Polynomial.h"

int main()
{
    Polynomial poly1{ 4, 5, 6, 7 };
    Polynomial poly2{ 6, 3, 2, 5 };
    std::pair<Polynomial, Polynomial> poly = poly1 / poly2;
    std::cout << poly.first << ' ' << poly.second;
}

