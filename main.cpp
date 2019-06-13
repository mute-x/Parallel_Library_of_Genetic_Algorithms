/* (c) 2019 ukrkyi */
#include <iostream>

#include "generator.h"
#include "finisher.h"

#include "genetic.h"

#include "selector.h"
#include "recombinator.h"
#include "mutator.h"

#include <numeric>

fitness_measure f0(double x, double y) {
	int a = 20;
	double b = 0.2;
	double c = 6.2831853;
	return 25 - (-a * exp(-b * sqrt(0.5 * (x*x/10000 + y*y/10000))) - exp(0.5 * (cos(c*x/100) + cos(c*y/100))) + a + exp(1));
}

auto range = std::make_tuple(std::make_pair(-1000., 1000.), std::make_pair(-1000., 1000.));

#include <chrono>
#include <atomic>

typedef std::chrono::high_resolution_clock::time_point timep;

inline timep get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

inline long long to_us(const std::chrono::high_resolution_clock::duration & d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

void dump(double x, double y) {
	std::cout << '(' << x<< ',' << y << ')' << ' ';
}

#define NUM_ITERATION	100
#define POPULATION_SIZE	30

int main()
{
	IterationFinisher finish(NUM_ITERATION);
	BestFitSelector sel;
	UniformPointRecombinator rec(1);
	RandomMutator mut(0.2);
	ParallelReplacementGenerator gen(sel, rec, mut);
	Genetic<double, double> algo(POPULATION_SIZE, f0, range, gen);

	algo.enable_output(dump);

	std::cout << POPULATION_SIZE << ' ' << NUM_ITERATION << std::endl;
	std::cout << std::get<0>(range).first << ' ' << std::get<0>(range).second << ' ' <<
		     std::get<1>(range).first << ' ' << std::get<1>(range).second << std::endl;

//	timep start = get_current_time_fenced();

	auto best = algo.run(finish);
	std::cout << '(' << std::get<0>(best) << ',' << std::get<1>(best) << ") " << std::apply(f0, best) << std::endl;

//	std::cout << to_us(get_current_time_fenced() - start) << std::endl;

	return 0;
}
