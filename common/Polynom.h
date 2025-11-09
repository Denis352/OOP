#ifndef POLYNOM_H
#define POLYNOM_H

#include "Complex.h"
#include <vector>
#include <string>

class Polynom {
private:
    std::vector<Complex> coefficients;

public:
    Polynom();
    Polynom(const std::vector<Complex>& coeffs);
    Polynom(const std::vector<double>& realCoeffs);
    
    std::vector<Complex> getCoefficients() const;
    void setCoefficients(const std::vector<Complex>& coeffs);
    int getDegree() const;
    
    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator*(const Complex& scalar) const;
    
    Polynom derivative() const;
    Complex evaluate(const Complex& x) const;
    
    std::string toString() const;
    static Polynom fromString(const std::string& str);
    
    bool isValid() const;
    void normalize();
};

#endif
