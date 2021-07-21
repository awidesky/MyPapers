#include <cmath>
#include <iostream>
#include <chrono>

#define TESTS 10

/*
in desktop with i5-4590S 3.00GHz, 4GB

mingw-w64 with x86_64-8.1.0-win32-seh-rt_v6-rev
mysqrt avg : 4667.81ms
stdlib avg : 10645.1ms
2.28times faster

MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 11.1.0
mysqrt avg : 4651.74ms
stdlib avg : 5255.95ms
1.13 tiems faster
*/
float fsqrt_(float f) {

	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);

}


double my_test() { 

	auto start = std::chrono::high_resolution_clock::now();

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = fsqrt_(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();

	std::cout << "mysqrt max : " << max << std::endl;
	return std::chrono::duration<double, std::milli>(end1 - start).count();
	
}

double lib_test() {

	auto start = std::chrono::high_resolution_clock::now();	

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = sqrtf(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();

	std::cout << "stdlib max : " << max << std::endl;
	return std::chrono::duration<double, std::milli>(end1 - start).count();
	
}


int main() {
    
	std::cout << "* warmup" << std::endl;
	for(int i = 0 ; i < 3 ; i++) {

		my_test();
		lib_test(); 
	}

	double my = 0.0, lib = 0.0;

	std::cout << "\n\n* test\n" << std::endl;
	for(int i = 0 ; i < TESTS ; i++) {

		my += my_test();
		lib += lib_test();

	}

	std::cout << "\n\nmysqrt avg : " << (my / TESTS) << "ms\nstdlib avg : " << (lib / TESTS) << "ms" << "\n";
	std::cout << "my sqrt is " << (lib/my) << " times faster than standard library" <<std::endl;

}