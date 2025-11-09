@echo off
echo Building Polynomial App with MinGW...

mkdir build 2>nul
cd build

echo Compiling common libraries...
g++ -std=c++17 -c ../common/Complex.cpp -o Complex.o
if errorlevel 1 (
    echo ERROR: Failed to compile Complex.cpp
    pause
    exit /b 1
)

g++ -std=c++17 -c ../common/Polynom.cpp -o Polynom.o
if errorlevel 1 (
    echo ERROR: Failed to compile Polynom.cpp
    pause
    exit /b 1
)

echo Compiling server...
g++ -std=c++17 -c ../server/main.cpp -o server_main.o
if errorlevel 1 (
    echo ERROR: Failed to compile server/main.cpp
    pause
    exit /b 1
)

echo Linking server...
g++ -std=c++17 server_main.o Complex.o Polynom.o -o polynomial_server.exe
if errorlevel 1 (
    echo ERROR: Failed to link server
    pause
    exit /b 1
)

echo Compiling client...
g++ -std=c++17 -c ../client/main.cpp -o client_main.o
if errorlevel 1 (
    echo ERROR: Failed to compile client/main.cpp
    pause
    exit /b 1
)

echo Linking client...
g++ -std=c++17 client_main.o Complex.o Polynom.o -o polynomial_client.exe
if errorlevel 1 (
    echo ERROR: Failed to link client
    pause
    exit /b 1
)

echo Build completed successfully!
echo.
echo Run server: polynomial_server.exe
echo Run client: polynomial_client.exe