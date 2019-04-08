/* (c) 2019 ukrkyi */
#ifndef SELECTOR_H
#define SELECTOR_H

#include "genetic.h"

#include <functional>
#include <random>

class Selector
{
public:
	virtual void set_population(std::vector<individual>&) = 0;
	virtual std::pair<size_t, size_t> get_pair() = 0;
};

class BestFitSelector : public Selector
{
	std::default_random_engine rng;
	std::discrete_distribution<size_t> elements;
public:
	BestFitSelector() : Selector(), rng(time(0)) {}
	virtual void set_population(std::vector<individual>&);
	virtual std::pair<size_t, size_t> get_pair();
};

#endif // SELECTOR_H
