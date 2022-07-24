
@pushd %~dp0

g++ --version

g++ -c -g -O3 -o my_asm_output.o speed_test_4_8.cpp
objdump -S -d my_asm_output.o > dump_4_8.txt

g++ speed_test_4_8.cpp -O3 -o speed_test_4_8.exe

speed_test.exe

pause