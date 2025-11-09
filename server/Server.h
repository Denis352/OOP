#ifndef SERVER_H
#define SERVER_H

#include "../common/Polynom.h"
#include <iostream>
#include <vector>

class Server {
public:
    Server() = default;
    
    void runLocalTests() {
        std::cout << "\n--- Testing Complex Numbers ---" << std::endl;
        testComplexNumbers();
        
        std::cout << "\n--- Testing Polynomial Operations ---" << std::endl;
        testPolynomialOperations();
        
        std::cout << "\n--- Testing Derivative ---" << std::endl;
        testDerivative();
        
        std::cout << "\n--- Testing Evaluation ---" << std::endl;
        testEvaluation();
    }
    
private:
    void testComplexNumbers() {
        Complex c1(1, 2);
        Complex c2(3, 4);
        
        std::cout << "c1 = " << c1.toString() << std::endl;
        std::cout << "c2 = " << c2.toString() << std::endl;
        std::cout << "c1 + c2 = " << (c1 + c2).toString() << std::endl;
        std::cout << "c1 * c2 = " << (c1 * c2).toString() << std::endl;
    }
    
    void testPolynomialOperations() {
        Polynom p1({Complex(1, 0), Complex(2, 0)});  // 1 + 2x
        Polynom p2({Complex(3, 0), Complex(4, 0)});  // 3 + 4x
        
        std::cout << "p1 = " << p1.toString() << std::endl;
        std::cout << "p2 = " << p2.toString() << std::endl;
        std::cout << "p1 + p2 = " << (p1 + p2).toString() << std::endl;
        std::cout << "p1 * p2 = " << (p1 * p2).toString() << std::endl;
    }
    
    void testDerivative() {
        Polynom p({Complex(1, 0), Complex(2, 0), Complex(3, 0)});  // 1 + 2x + 3x^2
        Polynom deriv = p.derivative();
        
        std::cout << "p = " << p.toString() << std::endl;
        std::cout << "p' = " << deriv.toString() << std::endl;
    }
    
    void testEvaluation() {
        Polynom p({Complex(1, 0), Complex(2, 0), Complex(1, 0)});  // 1 + 2x + x^2
        Complex x(2, 0);
        Complex result = p.evaluate(x);
        
        std::cout << "p = " << p.toString() << std::endl;
        std::cout << "p(" << x.toString() << ") = " << result.toString() << std::endl;
    }
};

#endif
