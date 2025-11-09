#include "FileServer.h"
#include <thread>
#include <chrono>

FileServer::FileServer(const std::string& reqFile, const std::string& respFile)
    : requestFile(reqFile), responseFile(respFile), running(false) {}

void FileServer::start() {
    running = true;
    std::cout << "File Server started. Monitoring: " << requestFile << std::endl;
    processLoop();
}

void FileServer::stop() {
    running = false;
}

void FileServer::processLoop() {
    while (running) {
        FileProtocol::Operation op;
        Polynom p1, p2;
        Complex point;
        
        if (FileProtocol::receiveRequest(requestFile, op, p1, p2, point)) {
            std::cout << "Processing request: " << FileProtocol::operationToString(op) << std::endl;
            
            try {
                Polynom result = executeOperation(op, p1, p2, point);
                FileProtocol::sendResponse(responseFile, result);
                std::cout << "Response sent: " << result.toString() << std::endl;
            } catch (const std::exception& e) {
                FileProtocol::sendError(responseFile, e.what());
                std::cout << "Error: " << e.what() << std::endl;
            }
            
            // Удаляем обработанный запрос
            std::remove(requestFile.c_str());
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

Polynom FileServer::executeOperation(FileProtocol::Operation op, 
                                   const Polynom& p1, const Polynom& p2, 
                                   const Complex& point) {
    switch (op) {
        case FileProtocol::ADD:
            return p1 + p2;
        case FileProtocol::SUBTRACT:
            return p1 - p2;
        case FileProtocol::MULTIPLY:
            return p1 * p2;
        case FileProtocol::DERIVATIVE:
            return p1.derivative();
        case FileProtocol::EVALUATE:
            return Polynom({p1.evaluate(point)}); // Возвращаем как полином степени 0
        default:
            throw std::runtime_error("Unknown operation");
    }
}