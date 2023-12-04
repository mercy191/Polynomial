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
	double*     coefficient;
    size_t      degree;

    void resize(int degree) {
        if (this->degree < degree) {
            double* new_coeeficient = new double[degree + 1] {0};
            for (size_t i = 0; i <= this->degree; ++i) {
                new_coeeficient[i] = this->coefficient[i];
            }
            delete[] this->coefficient;
            this->coefficient = new_coeeficient;
        }
    }

    void check_nullptr() const {
        if (this->coefficient == nullptr)
            throw std::runtime_error("Undefined behavior: uninitialized pointer");
    }

    void check_range(int index) const {
        if (index > this->degree || index < 0)
            throw std::out_of_range("Undefined behavior: invalid coefficient");
    }

public:
    inline Polynomial()
    {
        this->coefficient   = nullptr;
        this->degree        = 0;
    }

    inline Polynomial(const size_t deg)
        : coefficient(new double[deg + 1]{0}), degree(deg) {
    }

    inline Polynomial(const Polynomial& copy) { 
        this->coefficient   = new double[copy.degree + 1]{0};
        this->degree        = copy.degree;

        for (size_t i = 0; i <= copy.degree; ++i) {
            this->coefficient[i] = copy.coefficient[i];
        }        
    }

    inline Polynomial(Polynomial&& moved) noexcept {
        this->coefficient   = moved.coefficient;
        this->degree        = moved.degree;
        moved.coefficient   = nullptr;
        moved.degree        = 0;
    }

    inline Polynomial(std::initializer_list<double> ilist)
        : coefficient(new double[ilist.size()]), degree(ilist.size() - 1) {
        std::initializer_list<double>::iterator iter = ilist.begin();

        for (size_t i = 0; i < ilist.size(); ++i) {
            this->coefficient[i] = *iter;
            ++iter;
        }
    }

    inline ~Polynomial() noexcept {
        delete[] this->coefficient;
    }

    inline Polynomial& operator= (const Polynomial& copy) {
        copy.check_nullptr();

        if (this != &copy) {
            delete[] this->coefficient;
            this->coefficient   = new double(copy.degree + 1);
            this->degree        = copy.degree;

            for (size_t i = 0; i <= copy.degree; ++i) {
                this->coefficient[i] = copy.coefficient[i];
            }
        }

        return *this;
    }

    inline Polynomial& operator= (Polynomial&& moved) {
        moved.check_nullptr();

        if (this != &moved) {
            delete[] this->coefficient;
            this->coefficient   = moved.coefficient;
            this->degree        = moved.degree;
            moved.coefficient   = nullptr;
            moved.degree        = 0;
        }

        return *this;
    }

    inline Polynomial& operator= (std::initializer_list<double> ilist) {
        delete[] this->coefficient;
        this->coefficient = new double[ilist.size()];
        this->degree = ilist.size() - 1;

        std::initializer_list<double>::iterator iter = ilist.begin();
        for (size_t i = 0; i < ilist.size(); ++i) {
            coefficient[i] = *iter;
            ++iter;
        }

        return *this;
    }

    inline Polynomial operator+ (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        Polynomial result(std::max(this->degree, pol.degree));

        for (size_t i = 0; i <= this->degree; ++i) {
            result.coefficient[i] = coefficient[i];
        }

        for (size_t i = 0; i <= pol.degree; ++i) {
            result.coefficient[i] += pol.coefficient[i];
        }

        return result;
    }

    inline Polynomial operator- (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        Polynomial result(std::max(this->degree, pol.degree));

        for (size_t i = 0; i <= this->degree; ++i) {
            result.coefficient[i] = coefficient[i];
        }

        for (size_t i = 0; i <= pol.degree; ++i) {
            result.coefficient[i] -= pol.coefficient[i];
        }

        return result;
    }

    inline Polynomial operator* (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        size_t result_degree = this->degree + pol.degree;
        Polynomial result(result_degree);

        for (int i = pol.degree; i >= 0 ; --i) {
            size_t index = result_degree;
            for (int j = this->degree; j >= 0; --j) {
                result.coefficient[index] += pol.coefficient[i] * this->coefficient[j];
                index -= 1;
            }
            result_degree -= 1;
        }

        return result;
    }

    inline Polynomial operator* (const double number) const {
        this->check_nullptr();

        Polynomial result(this->degree);

        for (size_t i = 0; i <= result.degree; ++i) {
            result.coefficient[i] *= number;
        }

        return result;
    }

    inline Polynomial operator/ (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        Polynomial temp = Polynomial(*this);
        int result_degree = temp.degree - pol.degree;
        Polynomial result(result_degree);

        for (int i = 0; i <= result_degree; ++i) {
            result.coefficient[result_degree - i] = (temp.coefficient[temp.degree - i] / pol.coefficient[pol.degree]);
            for (int j = 0; j <= pol.degree; ++j) {
                temp.coefficient[temp.degree - j - i] -= (pol.coefficient[pol.degree - j] * result.coefficient[result_degree - i]);
            }
        }

        int temp_degree = temp.degree;
        for (int i = temp.degree; i >= 0; --i) {
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

    inline Polynomial operator/ (const double number) const {
        this->check_nullptr();

        if (number == 0)
            throw std::runtime_error("Undefined behavior: division by zero");

        Polynomial result(this->degree);

        for (size_t i = 0; i <= result.degree; ++i) {
            result.coefficient[i] /= number;
        }

        return result;
    }

    inline Polynomial& operator+= (const Polynomial& pol) {
        this->check_nullptr();
        pol.check_nullptr();

        if (this->degree < pol.degree) {
            this->resize(pol.degree);
        }

        for (size_t i = 0; i <= pol.degree; ++i) {
            this->coefficient[i] += pol.coefficient[i];
        }

        return *this;
    }

    inline Polynomial& operator-= (const Polynomial& pol) {
        this->check_nullptr();
        pol.check_nullptr();

        if (this->degree < pol.degree) {
            this->resize(pol.degree);
        }

        for (size_t i = 0; i <= pol.degree; ++i) {
            this->coefficient[i] -= pol.coefficient[i];
        }

        return *this;
    }

    inline Polynomial& operator*= (const Polynomial& pol) {
        this->check_nullptr();
        pol.check_nullptr();

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
        
        return *this = std::move(result);
    }

    inline Polynomial& operator*= (const double number) {
        this->check_nullptr();

        for (size_t i = 0; i <= this->degree; ++i) {
            this->coefficient[i] *= number;
        }

        return *this;
    }

    inline Polynomial& operator/= (const Polynomial& pol) {
        this->check_nullptr();
        pol.check_nullptr();

        int result_degree = this->degree - pol.degree;
        Polynomial result(result_degree);

        for (int i = 0; i <= result_degree; ++i) {
            result.coefficient[result_degree - i] = (this->coefficient[this->degree - i] / pol.coefficient[pol.degree]);
            for (int j = 0; j <= pol.degree; ++j) {
                this->coefficient[this->degree - j - i] -= (pol.coefficient[pol.degree - j] * result.coefficient[result_degree - i]);
            }
        }

        int temp_degree = this->degree;
        for (int i = this->degree; i >= 0; --i) {
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

    inline Polynomial& operator/= (const double number) {
        this->check_nullptr();

        if (number == 0)
            throw std::runtime_error("Undefined behavior: division by zero");

        for (size_t i = 0; i <= this->degree; ++i) {
            this->coefficient[i] /= number;
        }

        return *this;
    }

    inline bool operator== (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        if (this->degree == pol.degree) {
            for (size_t i = 0; i <= this->degree; ++i) {
                if (this->coefficient[i] != pol.coefficient[i])
                    return false;
            }

            return true;
        }

        return false;
    }

    inline bool operator!= (const Polynomial& pol) const {
        if (*this == pol) {
            return false;
        }

        return true;
    }

    inline bool operator< (const Polynomial& pol) const {
        this->check_nullptr();
        pol.check_nullptr();

        if (this->degree < pol.degree) {
            return true;
        }
        else if (this->degree == pol.degree) {
            for (size_t i = 0; i <= this->degree; ++i) {
                if (this->coefficient[i] > pol.coefficient[i])
                    return false;
            }
            return true;
        }

        return false;
    }

    inline bool operator> (const Polynomial& pol) const {
        if (*this < pol) {
            return false;
        }

        return true;
    }

    inline friend std::ostream& operator<< (std::ostream& os, const Polynomial& pol) {
        pol.check_nullptr();

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
        pol.check_nullptr();

        for (size_t i = 0; i <= pol.degree; ++i) {
            is >> pol.coefficient[i];
        }

        return is;
    }

    inline double& operator[] (const size_t index) {
        this->check_nullptr();
        this->check_range(index);

        return coefficient[index];
    }

    inline double operator[] (const size_t index) const {
        this->check_nullptr();
        this->check_range(index);

        return coefficient[index];
    } 

};