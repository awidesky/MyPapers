

#include <benchmark/benchmark.h>
#include <cmath>
#include <cstdlib>

float my_sqrt(const float f) {
	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);
}

/*
void Q_sqrt1(benchmark::State& state) {
  // Perform setup here
  volatile float f = 0.35f;
  for (auto _ : state) {
    sqrtn(f);
  }
}

void std_sqrt1(benchmark::State& state) {
  // Perform setup here
  volatile float f = 0.35f;
  for (auto _ : state) {
    std::sqrtf(f);
  }
}*/

void my_sqrt(benchmark::State& state) {
  for (auto _ : state) {
    my_sqrt((float)rand());
  }
}

void std_sqrt(benchmark::State& state) {
  for (auto _ : state) {
    std::sqrt((float)rand());
  }
}



// Run the benchmark
//BENCHMARK_MAIN();
// Register the function as a benchmark
BENCHMARK(my_sqrt);
BENCHMARK(std_sqrt);
