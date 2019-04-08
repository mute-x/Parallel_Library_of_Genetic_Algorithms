/* (c) 2019 ukrkyi */
#include "mutator.h"

std::vector<bool> RandomMutator::mutate(std::vector<bool> a)
{
	std::discrete_distribution<int> mutation({1 - prob, prob});
	if (mutation(rng)) {
		std::vector<bool> result(a);
		std::uniform_int_distribution<size_t> point(0, result.size() - 1);
		result[point(rng)].flip();
		return result;
	} else {
		return a;
	}
}
