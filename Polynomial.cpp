#include <iostream>
#include "Polynomial.h"

int main()
{
    Polynomial poly1 = { 1, 2, 3, 4 };
    Polynomial poly2 = { 5, 6, 7, 8 };
    Polynomial poly = poly1 / poly2;
    std::cout << poly;

}

