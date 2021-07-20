#include <cmath>
#include <iostream>
#include <chrono>

#define FROM 0.2F
#define TO 25.16F


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
	for (float ff = FROM ;; ff = std::nextafter(ff, TO)) {

		float f = fsqrt_(ff);
		if(max < f) max = f;

		if (ff - TO > 0.0001F) {
			break;
		}

	}

	auto end1 = std::chrono::steady_clock::now();
	auto diff = end1 - start;
	std::cout << "\n" << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	
}