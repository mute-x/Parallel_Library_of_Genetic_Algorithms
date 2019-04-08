/* (c) 2019 ukrkyi */
#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>
#include <random>

class Mutator
{
public:
	virtual std::vector<bool> mutate(std::vector<bool> a) = 0;
};

class RandomMutator: public Mutator
{
	std::default_random_engine rng;
	double prob;
public:
	RandomMutator(double mutation_probability) : Mutator(), rng(time(0)), prob(mutation_probability) {}
	virtual std::vector<bool> mutate(std::vector<bool> a);
};

#endif // MUTATOR_H
