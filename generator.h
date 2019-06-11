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
};

class FullReplacementGenerator: public Generator
{
public:
	FullReplacementGenerator(Selector& sel, Recombinator& rec, Mutator& m):
		Generator(sel, rec, m) {}
	virtual void new_generation(std::vector<individual> &population, fitness_function fitness);
};

class ParallelReplacementGenerator: public Generator
{
public:
	ParallelReplacementGenerator(Selector& sel, Recombinator& rec, Mutator& m):
		Generator(sel, rec, m) {}
	virtual void new_generation(std::vector<individual> &population, fitness_function fitness);
};

#endif // GENERATOR_H
