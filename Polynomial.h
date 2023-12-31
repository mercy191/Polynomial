//
//  Polynomial header
//  Операции с полиномами
//  Полином представлен в виде: P(n) = a0 + a1*x^1 + a2*x^2 + ... + an*x^n
//
//  Created by Иванов Никита on 18/11/2023
//

#pragma once
#include <iostream>

class Polynomial {

private:
	double*     coefficient;
    size_t      degree;
    size_t      size;

    void resize(int size);

    void check_range(int index) const;

public:
    Polynomial();

    Polynomial(const size_t deg);

    Polynomial(const Polynomial& copy);

    Polynomial(Polynomial&& moved) noexcept;

    Polynomial(std::initializer_list<double> ilist);

    ~Polynomial() noexcept;

    Polynomial& operator= (const Polynomial& copy);

    Polynomial& operator= (Polynomial&& moved);

    Polynomial& operator= (std::initializer_list<double> ilist);

    Polynomial operator+ (const Polynomial& pol) const;

    Polynomial operator- (const Polynomial& pol) const;

    Polynomial operator* (const Polynomial& pol) const;

    Polynomial operator* (const double number) const;

    Polynomial operator/ (const double number) const;

    Polynomial& operator+= (const Polynomial& pol);

    Polynomial& operator-= (const Polynomial& pol);

    Polynomial& operator*= (const Polynomial& pol);

    Polynomial& operator*= (const double number);

    Polynomial& operator/= (const double number);

    std::pair<Polynomial, Polynomial> operator/ (const Polynomial& pol) const;

    bool operator== (const Polynomial& pol) const;

    bool operator!= (const Polynomial& pol) const;

    friend std::ostream& operator<< (std::ostream& os, const Polynomial& pol);

    friend std::istream& operator>> (std::istream& is, Polynomial& pol);

    double& operator[] (const size_t index);

    const double& operator[] (const size_t index) const;

};