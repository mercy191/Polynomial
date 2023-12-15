#include <iostream>
#include "Polynomial.h"

int main()
{
    Polynomial poly1{ 4, 5, 6, 7 };
    Polynomial poly2{ 6, 3, 2, 5 };
    Polynomial poly3(5);
    Polynomial poly4 = poly1;

    std::cout << poly1 << '\n' << poly4 << '\n';

    poly3 = std::move(poly4);
    std::cout << poly3 << '\n' << poly4 << '\n';

    poly3 = poly1 + poly2;
    std::cout << poly3 << '\n';

    poly3 = poly1 - poly2;
    std::cout << poly3 << '\n';

    poly3 = poly1 * poly2;
    std::cout << poly3 << '\n';

    poly3 = poly1 * 5;
    std::cout << poly3 << '\n';

    std::pair<Polynomial, Polynomial> poly = poly1 / poly2;
    std::cout << poly.first << ' ' << poly.second << '\n';

    poly3 = poly1 / 5;
    std::cout << poly3 << '\n';

    poly3 += poly1;
    std::cout << poly3 << '\n';

    poly3 -= poly1;
    std::cout << poly3 << '\n';

    poly3 *= poly1;
    std::cout << poly3 << '\n';

    poly3 *= 7;
    std::cout << poly3 << '\n';

    poly3 /= 7;
    std::cout << poly3 << '\n';

    std::cout << (poly1 == poly2) << '\n';

    std::cout << (poly1 != poly2) << '\n';

    std::cout << poly3[2] << '\n';

    poly3[2] = 67;
    std::cout << poly3 << '\n';
}

