#include <cmath>
#include <iostream>
#include <ctime>

#define TESTS 10

/*
in desktop with i5-4590S 3.00GHz, 4GB
with g++ (GCC) 4.8.3

mysqrt avg : 4699.49ms
stdlib avg : 10568.1ms
my sqrt is 2.24878 times faster than standard library
*/
float fsqrt_(float f) {

	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);

}


double my_test() { 

	clock_t start = std::clock();

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = fsqrt_(f);
		if(max < re) max = re;

	}

	clock_t end1 = std::clock();

	std::cout << "mysqrt max : " << max << std::endl;
	return (double)(end1 - start);
	
}

double lib_test() {

	clock_t start = std::clock();

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = sqrtf(f);
		if(max < re) max = re;

	}

	clock_t end1 = std::clock();

	std::cout << "stdlib max : " << max << std::endl;
	return (double)(end1 - start);
	
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