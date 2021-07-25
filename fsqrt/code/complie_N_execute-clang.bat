
@pushd %~dp0

clang++ --version

clang speed_test.cpp -O3 -o speed_test.exe

speed_test.exe

pause