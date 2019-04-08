/* (c) 2019 ukrkyi */
#ifndef RECOMBINATOR_H
#define RECOMBINATOR_H

#include <random>
#include <vector>

class Recombinator
{
public:
	virtual std::vector<bool> crossover(std::vector<bool> a, std::vector<bool> b) = 0;
};

class UniformPointRecombinator : public Recombinator
{
	size_t pointNum;
	std::default_random_engine rng;
public:
	UniformPointRecombinator(size_t pointCount) : Recombinator(), pointNum(pointCount), rng(time(0)) {}
	virtual std::vector<bool> crossover(std::vector<bool> a, std::vector<bool> b);
};

#endif // RECOMBINATOR_H
