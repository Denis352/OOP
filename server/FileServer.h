#ifndef FILESERVER_H
#define FILESERVER_H

#include "../common/FileProtocol.h"
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

class FileServer {
private:
    std::string requestFile;
    std::string responseFile;
    bool running;

public:
    FileServer(const std::string& reqFile = "request.txt", 
               const std::string& respFile = "response.txt");
    
    void start();
    void stop();
    
private:
    void processLoop();
    Polynom executeOperation(FileProtocol::Operation op, 
                           const Polynom& p1, const Polynom& p2, 
                           const Complex& point);
};

#endif