@echo off
set DIR=build
if not exist "%DIR%" (mkdir "%DIR%")
cd "%DIR%"
cmake ..
cmake --build .
cd ..