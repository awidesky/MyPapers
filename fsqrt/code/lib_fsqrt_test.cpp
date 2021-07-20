#include <cmath>
#include <iostream>
#include <chrono>

#include <cstdlib>

int main() {
    
	


	std::cout << "hello!\n";
	auto start = std::chrono::high_resolution_clock::now();

	float max = 0.0F;
	for (int i = 0 ; i < 10000000 ; i++) {

		float f = sqrtf(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/30.0F)));
		if(max < f) max = f;

	}

	auto end1 = std::chrono::high_resolution_clock::now();
	auto diff = end1 - start;
	std::cout << "\n" << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	
}