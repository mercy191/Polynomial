//
//  Polynomial implementation
//  Операции с полиномами
//  Полином представлен в виде: P(n) = a0 + a1*x^1 + a2*x^2 + ... + an*x^n
//
//  Created by Иванов Никита on 18/11/2023
//

#include "Polynomial.h"

Polynomial::Polynomial()
{
    this->coefficient   = nullptr;
    this->degree        = 0;
    this->size          = 0;
}

Polynomial::Polynomial(const size_t deg)
    : coefficient(new double[deg + 1] {0}), degree(deg), size(deg + 1) {
}

Polynomial::Polynomial(const Polynomial& copy) {
    this->coefficient   = new double[copy.size] {0};
    this->degree        = copy.degree;
    this->size          = copy.size;

    for (size_t i = 0; i < copy.size; ++i) {
        this->coefficient[i] = copy.coefficient[i];
    }
}

Polynomial::Polynomial(Polynomial&& moved) noexcept {
    this->coefficient   = moved.coefficient;
    this->degree        = moved.degree;
    this->size          = moved.size;
    moved.coefficient   = nullptr;
    moved.degree        = 0;
    moved.size          = 0;
}

Polynomial::Polynomial(std::initializer_list<double> ilist)
    : coefficient(new double[ilist.size()]), degree(ilist.size() - 1), size(ilist.size()) {
    std::initializer_list<double>::iterator iter = ilist.begin();

    for (size_t i = 0; i < ilist.size(); ++i) {
        this->coefficient[i] = *iter;
        ++iter;
    }
}

Polynomial::~Polynomial() noexcept {
    delete[] this->coefficient;
}

Polynomial& Polynomial::operator= (const Polynomial& copy) {
    if (this != &copy) {
        delete[] this->coefficient;
        this->coefficient   = new double[copy.size];
        this->degree        = copy.degree;
        this->size          = copy.size;

        for (size_t i = 0; i < copy.size; ++i) {
            this->coefficient[i] = copy.coefficient[i];
        }
    }

    return *this;
}

Polynomial& Polynomial::operator= (Polynomial&& moved) {
    if (this != &moved) {
        delete[] this->coefficient;
        this->coefficient   = moved.coefficient;
        this->degree        = moved.degree;
        this->size          = moved.size;
        moved.coefficient   = nullptr;
        moved.degree        = 0;
        moved.size          = 0;
    }

    return *this;
}

Polynomial& Polynomial::operator= (std::initializer_list<double> ilist) {
    delete[] this->coefficient;
    this->coefficient   = new double[ilist.size()];
    this->degree        = ilist.size() - 1;
    this->size          = ilist.size();

    std::initializer_list<double>::iterator iter = ilist.begin();
    for (size_t i = 0; i < ilist.size(); ++i) {
        coefficient[i] = *iter;
        ++iter;
    }

    return *this;
}

Polynomial Polynomial::operator+ (const Polynomial& pol) const {
    Polynomial result(std::max(this->degree, pol.degree));

    for (size_t i = 0; i < this->size; ++i) {
        result.coefficient[i] = coefficient[i];
    }

    for (size_t i = 0; i < pol.size; ++i) {
        result.coefficient[i] += pol.coefficient[i];
    }

    return result;
}

Polynomial Polynomial::operator- (const Polynomial& pol) const {
    Polynomial result(std::max(this->degree, pol.degree));

    for (size_t i = 0; i < this->size; ++i) {
        result.coefficient[i] = coefficient[i];
    }

    for (size_t i = 0; i < pol.size; ++i) {
        result.coefficient[i] -= pol.coefficient[i];
    }

    return result;
}

Polynomial Polynomial::operator* (const Polynomial& pol) const {
    size_t result_degree = this->degree + pol.degree;
    Polynomial result(result_degree);

    for (int i = pol.size - 1; i >= 0; --i) {
        size_t index = result_degree;
        for (int j = this->size - 1; j >= 0; --j) {
            result.coefficient[index] += pol.coefficient[i] * this->coefficient[j];
            index -= 1;
        }
        result_degree -= 1;
    }

    return result;
}

Polynomial Polynomial::operator* (const double number) const {
    Polynomial result(this->degree);

    for (size_t i = 0; i < this->size; ++i) {
        result.coefficient[i] += this->coefficient[i] * number;
    }

    return result;
}

Polynomial Polynomial::operator/ (const Polynomial& pol) const {
    Polynomial temp     = Polynomial(*this);
    int result_degree   = temp.degree - pol.degree;
    int result_size     = result_degree + 1;
    Polynomial result(result_degree);

    for (int i = 0; i < result_size; ++i) {
        result.coefficient[result_size - i - 1] = (temp.coefficient[temp.size - i - 1] / pol.coefficient[pol.size - 1]);
        for (int j = 0; j < pol.size; ++j) {
            temp.coefficient[temp.size - j - i - 1] -= (pol.coefficient[pol.size - j - 1] * result.coefficient[result_size - i - 1]);
        }
    }

    int temp_degree = temp.degree;
    for (int i = temp.size - 1; i >= 0; --i) {
        if (temp.coefficient[i] != 0.0)
            break;
        else
            --temp_degree;
    }
    temp.degree = temp_degree;

    if (temp.degree != 0) {
        std::cout << "Ostatok: " << temp << std::endl;
    }

    return result;
}

Polynomial Polynomial::operator/ (const double number) const {
    if (number == 0)
        throw std::runtime_error("Undefined behavior: division by zero");

    Polynomial result(this->degree);

    for (size_t i = 0; i < this->size; ++i) {
        result.coefficient[i] += this->coefficient[i] / number;
    }

    return result;
}

Polynomial& Polynomial::operator+= (const Polynomial& pol) {
    if (this->size < pol.size) {
        this->resize(pol.size);
    }

    for (size_t i = 0; i < pol.size; ++i) {
        this->coefficient[i] += pol.coefficient[i];
    }

    return *this;
}

Polynomial& Polynomial::operator-= (const Polynomial& pol) {
    if (this->size < pol.size) {
        this->resize(pol.size);
    }

    for (size_t i = 0; i < pol.size; ++i) {
        this->coefficient[i] -= pol.coefficient[i];
    }

    return *this;
}

Polynomial& Polynomial::operator*= (const Polynomial& pol) {
    size_t result_degree = this->degree + pol.degree;
    Polynomial result(result_degree);

    for (int i = pol.size - 1; i >= 0; --i) {
        size_t index = result_degree;
        for (int j = this->size - 1; j >= 0; --j) {
            result.coefficient[index] += pol.coefficient[i] * this->coefficient[j];
            index -= 1;
        }
        result_degree -= 1;
    }

    return *this = std::move(result);
}

Polynomial& Polynomial::operator*= (const double number) {
    for (size_t i = 0; i < this->size; ++i) {
        this->coefficient[i] *= number;
    }

    return *this;
}

Polynomial& Polynomial::operator/= (const Polynomial& pol) {
    int result_degree   = this->degree - pol.degree;
    int result_size     = result_degree + 1;
    Polynomial result(result_degree);

    for (int i = 0; i < result_size; ++i) {
        result.coefficient[result_size - i - 1] = (this->coefficient[this->size - i - 1] / pol.coefficient[pol.size - 1]);
        for (int j = 0; j < pol.size; ++j) {
            this->coefficient[this->size - j - i - 1] -= (pol.coefficient[pol.size - j - 1] * result.coefficient[result_size - i - 1]);
        }
    }

    int temp_degree = this->degree;
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficient[i] != 0.0)
            break;
        else
            --temp_degree;
    }
    this->degree = temp_degree;

    if (this->degree != 0) {
        std::cout << "Ostatok: " << *this << std::endl;
    }

    return *this = std::move(result);
}

Polynomial& Polynomial::operator/= (const double number) {
    if (number == 0)
        throw std::runtime_error("Undefined behavior: division by zero");

    for (size_t i = 0; i < this->size; ++i) {
        this->coefficient[i] /= number;
    }

    return *this;
}

bool Polynomial::operator== (const Polynomial& pol) const {
    if (this->degree == pol.degree) {
        for (size_t i = 0; i < this->size; ++i) {
            if (this->coefficient[i] != pol.coefficient[i])
                return false;
        }

        return true;
    }

    return false;
}

bool Polynomial::operator!= (const Polynomial& pol) const {
    if (*this == pol) {
        return false;
    }

    return true;
}

std::ostream& operator<< (std::ostream& os, const Polynomial& pol) {
    if (pol.size != 0)
    {
        os << pol.coefficient[0];
        for (size_t i = 1; i < pol.size; ++i) {
            if (pol.coefficient[i] > 0) {
                os << " + " << pol.coefficient[i] << "x^" << i;
            }
            else if (pol.coefficient[i] < 0) {
                os << " - " << -pol.coefficient[i] << "x^" << i;
            }
        }

        return os;
    }
}

std::istream& operator>> (std::istream& is, Polynomial& pol) {
    for (size_t i = 0; i < pol.size; ++i) {
        is >> pol.coefficient[i];
    }

    return is;
}

double& Polynomial::operator[] (const size_t index) {
    this->check_range(index);

    return coefficient[index];
}

const double& Polynomial::operator[] (const size_t index) const {
    this->check_range(index);

    return coefficient[index];
}

void Polynomial::resize(int size) {
    double* new_coeeficient = new double[size] {0};
    for (size_t i = 0; i < this->size; ++i) {
        new_coeeficient[i] = this->coefficient[i];
    }
    delete[] this->coefficient;
    this->coefficient = new_coeeficient;
}

void Polynomial::check_range(int index) const {
    if (index > this->degree || index < 0)
        throw std::out_of_range("Undefined behavior: invalid coefficient");
}