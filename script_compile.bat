@echo off
cd build
cmake --build . --config Release
cd Release
main.exe