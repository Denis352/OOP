cmake_minimum_required(VERSION 3.16)
project(PolynomialApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка Qt6
set(CMAKE_PREFIX_PATH "C:/Qt")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

message(STATUS "Qt6 version: ${Qt6_VERSION}")

# Common library
add_library(common
    common/Complex.cpp
    common/Polynom.cpp
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Server executable
add_executable(polynomial_server
    server/main.cpp
    server/QtServer.cpp
)

target_link_libraries(polynomial_server common Qt6::Core Qt6::Network)

# Client executable with GUI - ТОЛЬКО ОДИН РАЗ!
add_executable(polynomial_client
    client/main.cpp
    client/MainWindow.cpp
)

target_link_libraries(polynomial_client common Qt6::Core Qt6::Widgets Qt6::Network)