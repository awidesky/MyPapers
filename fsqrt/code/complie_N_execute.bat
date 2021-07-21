
@pushd %~dp0

g++ --version

g++ -c -g -o my_asm_output.o speed_test.cpp
objdump -S -d my_asm_output.o > dump.txt

g++ speed_test.cpp -O3 -o speed_test.exe

speed_test.exe

pause