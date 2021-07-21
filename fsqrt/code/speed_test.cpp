#include <cmath>
#include <iostream>
#include <chrono>

float fsqrt_(float f) {

	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);

}


void my_test() { 

	auto start = std::chrono::high_resolution_clock::now();

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = fsqrt_(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();
	auto diff = end1 - start;
	std::cout << "mysqrt : " << std::chrono::duration <double, std::nano> (diff).count() << " ms" << std::endl;
	
}

void lib_test() {

	auto start = std::chrono::high_resolution_clock::now();	

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = sqrtf(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();
	auto diff = end1 - start;
	std::cout << "stdlib : " << std::chrono::duration <double, std::nano> (diff).count() << " ms" << std::endl;
	
}


int main() {
    
	std::cout << "warmup" << std::endl;
	for(int i = 0 ; i < 3 ; i++) {

		my_test();
		lib_test();

	}


	std::cout << "\n\ntest\n" << std::endl;
	for(int i = 0 ; i < 5 ; i++) {

		my_test();
		lib_test();

	}

}