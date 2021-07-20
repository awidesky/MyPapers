#include <cmath>
#include <iostream>
#include <chrono>

#define FROM 0.2F
#define TO 10.16F

int main() {
    
	std::cout << "hello!\n";
	auto start = std::chrono::high_resolution_clock::now();

	float max = 0.0F;
	for (float ff = FROM ;; ff = std::nextafter(ff, TO)) {

		float f = sqrtf(ff);
		if(max < f) max = f;

		if (ff - TO > 0.0001F) {
			break;
		}

	}

	auto end1 = std::chrono::high_resolution_clock::now();
	auto diff = end1 - start;
	std::cout << "\n" << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	
}