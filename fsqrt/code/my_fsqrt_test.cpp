#include <cmath>
#include <iostream>
#include <chrono>

#include <cstdlib>


float fsqrt_(float f) {

	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);

}

int main() {
        

	std::cout << "hello!\n";
	auto start = std::chrono::steady_clock::now();

	float max = 0.0F;
	for (int i = 0 ; i < 10000000 ; i++) {

		float f = fsqrt_(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/30.0F)));
		if(max < f) max = f;

	}

	auto end1 = std::chrono::steady_clock::now();
	auto diff = end1 - start;
	std::cout << "\n" << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	
}