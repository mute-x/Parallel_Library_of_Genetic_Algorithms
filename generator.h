/* (c) 2019 ukrkyi */
#ifndef GENERATOR_H
#define GENERATOR_H

#include "genetic.h"
#include "tbb/tbb.h"


class Selector;
class Recombinator;
class Mutator;

class Generator
{
protected:
	Selector& selector;
	Recombinator& recombinator;
	Mutator& mutator;
public:
	Generator(Selector& sel, Recombinator& rec, Mutator& m);
	// TODO make population & fitness passed to the class only once
	virtual void create_population(std::vector<individual>& population, fitness_function fitness);
	virtual void new_generation(std::vector<individual> &population, fitness_function fitness) = 0;
	virtual void new_generation_parallel(std::vector<individual> &population, fitness_function fitness) = 0;
};

class FullReplacementGenerator: public Generator
{
public:
	FullReplacementGenerator(Selector& sel, Recombinator& rec, Mutator& m):
		Generator(sel, rec, m) {}
	virtual void new_generation(std::vector<individual> &population, fitness_function fitness);
	virtual void new_generation_parallel(std::vector<individual> &population, fitness_function fitness);
};


class CalculateFitness {
	std::vector<individual> &population;
	fitness_function fitnessFunction;
public:
	CalculateFitness(std::vector<individual> &population,
					 fitness_function &fit) : population(population),
											  fitnessFunction(fit) {
		population = population;
		fitnessFunction = fit;
	}

	void operator()(const tbb::blocked_range<size_t> &r) const {
		for (size_t i = r.begin(); i != r.end(); ++i) {
			population[i].second = fitnessFunction(population[i].first);
		}
	}

};

#endif // GENERATOR_H
