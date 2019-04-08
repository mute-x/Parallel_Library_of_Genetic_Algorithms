/* (c) 2019 ukrkyi */
#include <iostream>

#include "generator.h"
#include "finisher.h"

#include "genetic.h"

#include "selector.h"
#include "recombinator.h"
#include "mutator.h"

#include <numeric>

#define NUM_BITS 5

std::pair<int, int> convert(std::vector<bool>& genome) {
	std::pair<int, int> result(std::accumulate(genome.rbegin(), genome.rbegin() + NUM_BITS - 1, 0, [](int x, int y) { return (x << 1) + y; })
				   * (*(genome.rbegin() + NUM_BITS - 1) ? -1 : 1),
					   std::accumulate(genome.rbegin() + NUM_BITS, genome.rbegin() + NUM_BITS * 2 - 1, 0,
							       [](int x, int y) { return (x << 1) + y; })
				   * (*(genome.rbegin() + NUM_BITS * 2 - 1) ? -1 : 1));
	return result;
}

fitness_measure f0(int x, int y) {
	return 1000 - 2*(x*x + y*y);
}

fitness_measure f(std::vector<bool>& genome) {
	std::pair<int, int> data = convert(genome);
	return f0(data.first, data.second);
}

void dump(std::vector<bool> & genome) {
	std::pair<int, int> data = convert(genome);
	std::cout << '(' << data.first << ',' << data.second << ')' << ' ';
}

#define NUM_ITERATION	100
#define POPULATION_SIZE	30

int main()
{
	IterationFinisher finish(NUM_ITERATION);
	BestFitSelector sel;
	UniformPointRecombinator rec(1);
	RandomMutator mut(0.1);
	FullReplacementGenerator gen(sel, rec, mut);
	Genetic algo(NUM_BITS * 2, POPULATION_SIZE, f, gen);

	algo.enable_output(dump);

	std::cout << POPULATION_SIZE << ' ' << NUM_ITERATION << std::endl;
	std::cout << -16 << ' ' << 15 << ' ' << -16 << ' ' << 15 << std::endl;
	for (int i=-16; i < 16; i++) {
		for (int j = -16; j < 16; j++)
			std::cout << f0(i,j) << ' ';
		std::cout << std::endl;
	}
	algo.run(finish);

	return 0;
}
