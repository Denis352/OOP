#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0);
    
    double getReal() const;
    double getImag() const;
    void setReal(double r);
    void setImag(double i);
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    
    double magnitude() const;
    double phase() const;
    Complex conjugate() const;
    std::string toString() const;
    
    static Complex fromString(const std::string& str);
};

#endif