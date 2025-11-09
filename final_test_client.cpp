#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
    std::cout << "=== Polynomial Client Test ===" << std::endl;
    
    // Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed!" << std::endl;
        return 1;
    }
    
    // Создаем UDP сокет
    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed!" << std::endl;
        WSACleanup();
        return 1;
    }
    
    // Адрес сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // JSON запрос на сложение полиномов
    std::string jsonRequest = R"({
        "operation": "add",
        "polynom1": [
            {"real": 1, "imag": 0},
            {"real": 2, "imag": 0}
        ],
        "polynom2": [
            {"real": 3, "imag": 0},
            {"real": 4, "imag": 0}
        ]
    })";
    
    std::cout << "Sending request to server..." << std::endl;
    std::cout << "Request: " << jsonRequest << std::endl;
    
    // Отправляем запрос
    int sendResult = sendto(clientSocket, jsonRequest.c_str(), jsonRequest.length(), 0, 
                           (sockaddr*)&serverAddr, sizeof(serverAddr));
    
    if (sendResult == SOCKET_ERROR) {
        std::cout << "Send failed! Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Request sent successfully!" << std::endl;
    std::cout << "Waiting for server response..." << std::endl;
    
    // Ждем ответ
    char buffer[1024];
    sockaddr_in fromAddr;
    int fromLen = sizeof(fromAddr);
    
    // Устанавливаем таймаут 5 секунд
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    
    int bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer)-1, 0, 
                                (sockaddr*)&fromAddr, &fromLen);
    
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "=== SERVER RESPONSE ===" << std::endl;
        std::cout << buffer << std::endl;
        std::cout << "=== TEST PASSED ===" << std::endl;
    } else {
        std::cout << "No response received (timeout after 5 seconds)" << std::endl;
        std::cout << "=== TEST FAILED ===" << std::endl;
    }
    
    closesocket(clientSocket);
    WSACleanup();
    
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}