/* (c) 2019 ukrkyi */
#include "genetic.h"

#include "finisher.h"
#include "generator.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <iostream>

Genetic::Genetic(size_t genomeLength, size_t populationSize, fitness_function f, Generator& gen):
	population(populationSize, individual(std::vector<bool>(genomeLength), 0)),
	generator(gen), function(f), dump_function(nullptr)
{
	std::srand(std::time(0));
}

void Genetic::dump_population()
{
	if (dump_function != nullptr) {
		for (auto & ind : population)
			dump_function(ind.first);
		std::cout << std::endl;
	}
}

std::vector<bool> Genetic::run(Finisher &condition)
{
	condition.start();
	generator.create_population(population, function);
	dump_population();
	while (!condition.is_finish(population)) {
		generator.new_generation_parallel(population, function);
		dump_population();
	}
	return std::max_element(population.begin(), population.end(), [](individual& a, individual& b){ return a.second < b.second;})->first;
}

void Genetic::enable_output(void (*dumper)(std::vector<bool>&))
{
	dump_function = dumper;
}
