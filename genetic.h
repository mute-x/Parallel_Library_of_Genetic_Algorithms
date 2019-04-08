/* (c) 2019 ukrkyi */
#ifndef GENETIC_H
#define GENETIC_H

#include <vector>

typedef double fitness_measure;

typedef fitness_measure (*fitness_function)(std::vector<bool>&);
typedef std::pair<std::vector<bool>, fitness_measure> individual;

class Generator;
class Finisher;

class Genetic
{
	std::vector<individual> population;
	Generator& generator;
	fitness_function function;
	void (*dump_function)(std::vector<bool>&);
	void dump_population();
public:
	Genetic(size_t genomeLength, size_t populationSize, fitness_function f, Generator& gen);
	std::vector<bool> run(Finisher& condition);
	void enable_output(void (*dumper)(std::vector<bool>&));
};

#endif // GENETIC_H
