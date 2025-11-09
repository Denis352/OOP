#ifndef FILEPROTOCOL_H
#define FILEPROTOCOL_H

#include "Complex.h"
#include "Polynom.h"
#include <string>
#include <fstream>
#include <iostream>

class FileProtocol {
public:
    enum Operation {
        ADD,
        SUBTRACT, 
        MULTIPLY,
        DERIVATIVE,
        EVALUATE,
        UNKNOWN
    };

    static bool sendRequest(const std::string& filename, Operation op, 
                          const Polynom& p1, const Polynom& p2 = Polynom(),
                          const Complex& point = Complex());
    
    static bool receiveRequest(const std::string& filename, Operation& op,
                             Polynom& p1, Polynom& p2, Complex& point);
    
    static bool sendResponse(const std::string& filename, const Polynom& result);
    static bool sendError(const std::string& filename, const std::string& error);
    
    static bool receiveResponse(const std::string& filename, Polynom& result, std::string& error);
    
    static Operation stringToOperation(const std::string& str);
    static std::string operationToString(Operation op);
    
    static Polynom polynomFromString(const std::string& str);
    static std::string polynomToString(const Polynom& poly);
    
    static Complex complexFromString(const std::string& str);
    static std::string complexToString(const Complex& c);
};

#endif