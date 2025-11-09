#include "Complex.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }
void Complex::setReal(double r) { real = r; }
void Complex::setImag(double i) { imag = i; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag,
        real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) throw std::runtime_error("Division by zero");

    return Complex((real * other.real + imag * other.imag) / denominator,
        (imag * other.real - real * other.imag) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

double Complex::magnitude() const {
    return std::sqrt(real * real + imag * imag);
}

double Complex::phase() const {
    return std::atan2(imag, real);
}

Complex Complex::conjugate() const {
    return Complex(real, -imag);
}

std::string Complex::toString() const {
    std::ostringstream oss;
    oss << real;
    if (imag >= 0) oss << "+" << imag << "i";
    else oss << imag << "i";
    return oss.str();
}

Complex Complex::fromString(const std::string& str) {
    double r = 0, i = 0;
    char plus, i_char;
    std::istringstream iss(str);
    iss >> r >> plus >> i >> i_char;
    return Complex(r, i);
}