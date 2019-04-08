/* (c) 2019 ukrkyi */
#include "selector.h"

#include <cstdlib>

void BestFitSelector::set_population(std::vector<individual> &new_population)
{
	fitness_measure fitnessSum = 0;
	for (auto ind : new_population)
		fitnessSum += ind.second;
	// TODO: rewrite this using boost::transform_iterator (so we will not use floating-points)
	elements = std::discrete_distribution<size_t>(
				new_population.size(), 0, new_population.size(),
				[new_population](size_t i){ return new_population[i].second; });
}

std::pair<size_t, size_t> BestFitSelector::get_pair()
{
	auto num1 = elements(rng), num2 = elements(rng);
	return std::pair<size_t, size_t> (num1, num2);
}
