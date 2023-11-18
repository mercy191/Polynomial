//
//  Polynomial header
//  Операции с полиномами
//  Полином представлен в виде: P(n) = a0 + a1*x^1 + a2*x^2 + ... + an*x^n
//
//  Created by Иванов Никита on 18/11/2023
//

#pragma once
#include <ostream>
#include <istream>

class Polynomial {

private:
    double* coefficient;
    size_t      degree;
public:
    inline Polynomial()
    {}

    inline Polynomial(const size_t deg)
        : coefficient(new double[deg + 1]), degree(deg) {
    }

    inline Polynomial(const Polynomial& copy) {
        this->coefficient = new double(copy.degree + 1);
        this->degree = copy.degree;

        for (int i = 0; i <= copy.degree; ++i) {
            this->coefficient[i] = copy.coefficient[i];
        }
    }

    inline Polynomial(Polynomial&& moved) noexcept {
        this->coefficient = moved.coefficient;
        this->degree = moved.degree;
        moved.coefficient = nullptr;
        moved.degree = 0;
    }

    inline Polynomial(std::initializer_list<double> ilist)
        : coefficient(new double[ilist.size()]), degree(ilist.size() - 1) {
        std::initializer_list<double>::iterator iter = ilist.begin();
        for (int i = 0; i < ilist.size(); ++i) {
            this->coefficient[i] = *iter;
            ++iter;
        }
    }

    inline ~Polynomial() noexcept {
        delete[] this->coefficient;
    }

    inline Polynomial& operator= (const Polynomial& copy) {
        if (this != &copy) {
            delete[] this->coefficient;
            this->coefficient = new double(copy.degree + 1);
            this->degree = copy.degree;
            for (int i = 0; i <= copy.degree; ++i) {
                coefficient[i] = copy.coefficient[i];
            }
        }

        return *this;
    }

    inline Polynomial& operator= (Polynomial&& moved) {
        if (this != &moved) {
            this->coefficient = moved.coefficient;
            this->degree = moved.degree;
            moved.coefficient = nullptr;
            moved.degree = 0;
        }

        return *this;
    }

    inline Polynomial& operator= (std::initializer_list<double> ilist) {
        delete[] this->coefficient;
        this->coefficient = new double[ilist.size()];
        this->degree = ilist.size() - 1;

        std::initializer_list<double>::iterator iter = ilist.begin();
        for (int i = 0; i < ilist.size(); ++i) {
            coefficient[i] = *iter;
            ++iter;
        }

        return *this;
    }

    inline Polynomial operator+ (const Polynomial& pol) const {
        Polynomial result(std::max(this->degree, pol.degree) + 1);

        for (int i = 0; i <= this->degree; ++i) {
            result.coefficient[i] = coefficient[i];
        }

        for (int i = 0; i <= pol.degree; ++i) {
            result.coefficient[i] += pol.coefficient[i];
        }

        return result;
    }

    inline Polynomial operator- (const Polynomial& pol) const {
        Polynomial result(std::max(this->degree, pol.degree) + 1);

        for (int i = 0; i <= this->degree; ++i) {
            result.coefficient[i] = coefficient[i];
        }

        for (int i = 0; i <= pol.degree; ++i) {
            result.coefficient[i] -= pol.coefficient[i];
        }

        return result;
    }

    inline Polynomial operator* (const Polynomial& pol) const {
        size_t result_degree = this->degree + pol.degree;
        Polynomial result(result_degree);

        for (int i = pol.degree; i >= 0; --i) {
            size_t index = result_degree;
            for (int j = this->degree; j >= 0; --j) {
                result.coefficient[index] += pol.coefficient[i] * this->coefficient[j];
                index -= 1;
            }
            result_degree -= 1;
        }

        return result;
    }

    inline Polynomial operator/ (const Polynomial& pol) {
        if (this->degree < pol.degree) {
            return *this;
        }

        Polynomial result(this->degree - pol.degree);
        for (size_t i = 0; this->degree - i >= pol.degree; ++i) {
            result.coefficient[i] = (this->coefficient[i] / pol.coefficient[0]);
            for (size_t j = 0; j <= pol.degree; ++j) {
                this->coefficient[j + i] = this->coefficient[j + i] - (result[i] * pol.coefficient[j]);
            }
        }

        return result;
    }

    inline Polynomial& operator+= (const Polynomial& pol) {
        if (this->degree < pol.degree) {
            double* new_coeeficient = new double[pol.degree + 1] {0};
            for (int i = 0; i <= this->degree; ++i) {
                new_coeeficient[i] = this->coefficient[i];
            }
            delete[] this->coefficient;
            this->coefficient = new_coeeficient;
        }

        for (int i = 0; i <= pol.degree; ++i) {
            this->coefficient[i] += pol.coefficient[i];
        }

        return *this;
    }

    inline Polynomial& operator-= (const Polynomial& pol) {
        if (this->degree < pol.degree) {
            double* new_coeeficient = new double[pol.degree + 1] {0};
            for (int i = 0; i <= this->degree; ++i) {
                new_coeeficient[i] = this->coefficient[i];
            }
            delete[] this->coefficient;
            this->coefficient = new_coeeficient;
        }

        for (int i = 0; i <= pol.degree; ++i) {
            this->coefficient[i] -= pol.coefficient[i];
        }

        return *this;
    }

    inline bool operator== (const Polynomial& pol) const {
        if (this->degree == pol.degree) {
            for (int i = 0; i <= this->degree; ++i) {
                if (this->coefficient[i] != pol.coefficient[i])
                    return false;
            }

            return true;
        }

        return false;
    }

    inline friend std::ostream& operator<< (std::ostream& os, const Polynomial& pol) {
        os << pol.coefficient[0];
        for (size_t i = 1; i <= pol.degree; ++i) {
            if (pol.coefficient[i] > 0) {
                os << " + " << pol.coefficient[i] << "x^" << i;
            }
            else if (pol.coefficient[i] < 0) {
                os << " - " << -pol.coefficient[i] << "x^" << i;
            }
        }

        return os;
    }

    inline friend std::istream& operator>> (std::istream& is, Polynomial& pol) {
        for (int i = 0; i <= pol.degree; ++i) {
            is >> pol.coefficient[i];
        }

        return is;
    }

    inline double operator[] (const size_t i) const {
        return coefficient[i];
    }
};