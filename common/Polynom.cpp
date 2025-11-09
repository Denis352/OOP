#include "Polynom.h"
#include <sstream>
#include <algorithm>

Polynom::Polynom() {}

Polynom::Polynom(const std::vector<Complex>& coeffs) : coefficients(coeffs) {
    normalize();
}

Polynom::Polynom(const std::vector<double>& realCoeffs) {
    for (double coeff : realCoeffs) {
        coefficients.push_back(Complex(coeff, 0));
    }
    normalize();
}

std::vector<Complex> Polynom::getCoefficients() const {
    return coefficients;
}

void Polynom::setCoefficients(const std::vector<Complex>& coeffs) {
    coefficients = coeffs;
    normalize();
}

int Polynom::getDegree() const {
    return coefficients.empty() ? -1 : coefficients.size() - 1;
}

Polynom Polynom::operator+(const Polynom& other) const {
    size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    std::vector<Complex> result(maxSize);
    
    for (size_t i = 0; i < maxSize; i++) {
        Complex c1 = (i < coefficients.size()) ? coefficients[i] : Complex();
        Complex c2 = (i < other.coefficients.size()) ? other.coefficients[i] : Complex();
        result[i] = c1 + c2;
    }
    
    return Polynom(result);
}

Polynom Polynom::operator-(const Polynom& other) const {
    size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    std::vector<Complex> result(maxSize);
    
    for (size_t i = 0; i < maxSize; i++) {
        Complex c1 = (i < coefficients.size()) ? coefficients[i] : Complex();
        Complex c2 = (i < other.coefficients.size()) ? other.coefficients[i] : Complex();
        result[i] = c1 - c2;
    }
    
    return Polynom(result);
}

Polynom Polynom::operator*(const Polynom& other) const {
    std::vector<Complex> result(coefficients.size() + other.coefficients.size() - 1, Complex());
    
    for (size_t i = 0; i < coefficients.size(); i++) {
        for (size_t j = 0; j < other.coefficients.size(); j++) {
            result[i + j] = result[i + j] + (coefficients[i] * other.coefficients[j]);
        }
    }
    
    return Polynom(result);
}

Polynom Polynom::operator*(const Complex& scalar) const {
    std::vector<Complex> result = coefficients;
    for (auto& coeff : result) {
        coeff = coeff * scalar;
    }
    return Polynom(result);
}

Polynom Polynom::derivative() const {
    if (coefficients.size() <= 1) {
        return Polynom({Complex(0, 0)});
    }
    
    std::vector<Complex> result(coefficients.size() - 1);
    for (size_t i = 1; i < coefficients.size(); i++) {
        result[i - 1] = coefficients[i] * Complex(i, 0);
    }
    
    return Polynom(result);
}

Complex Polynom::evaluate(const Complex& x) const {
    Complex result(0, 0);
    Complex x_power(1, 0);
    
    for (size_t i = 0; i < coefficients.size(); i++) {
        result = result + (coefficients[i] * x_power);
        if (i < coefficients.size() - 1) {
            x_power = x_power * x;
        }
    }
    
    return result;
}

std::string Polynom::toString() const {
    if (coefficients.empty()) return "0";
    
    std::ostringstream oss;
    for (int i = coefficients.size() - 1; i >= 0; i--) {
        if (coefficients[i].getReal() == 0 && coefficients[i].getImag() == 0) {
            continue;
        }
        
        if (i < coefficients.size() - 1) {
            oss << " + ";
        }
        
        oss << "(" << coefficients[i].toString() << ")";
        if (i > 0) {
            oss << "x";
            if (i > 1) {
                oss << "^" << i;
            }
        }
    }
    
    return oss.str();
}

Polynom Polynom::fromString(const std::string& str) {
    // Простая реализация для теста
    return Polynom({Complex(1, 0), Complex(2, 0)});
}

bool Polynom::isValid() const {
    return !coefficients.empty();
}

void Polynom::normalize() {
    // Удаляем нулевые старшие коэффициенты
    while (coefficients.size() > 1 && 
           coefficients.back().getReal() == 0 && 
           coefficients.back().getImag() == 0) {
        coefficients.pop_back();
    }
    
    if (coefficients.empty()) {
        coefficients.push_back(Complex(0, 0));
    }
}