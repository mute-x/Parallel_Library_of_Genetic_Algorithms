/* (c) 2019 ukrkyi */
#include "recombinator.h"

#include <algorithm>
#include <functional>

std::vector<bool> UniformPointRecombinator::crossover(std::vector<bool> a, std::vector<bool> b)
{
	std::vector<bool> result(a.size());
	std::uniform_int_distribution<size_t> pointGen(1, a.size() - 1);
	std::vector<size_t> points(pointNum + 2);
	std::generate(points.begin() + 1, points.end() - 1, std::bind(pointGen, rng));
	*(points.begin()) = 0;
	*(points.end()-1) = result.size();
	std::sort(points.begin(), points.end());
	for (size_t i = 0; i < points.size() - 1; i++ ){
		std::vector<bool>::iterator start, end;
		if (i % 2) {
			start = b.begin() + points[i];
			end = b.begin() + points[i+1];
		} else {
			start = a.begin() + points[i];
			end = a.begin() + points[i+1];
		}
		if (start != end)
			std::copy(start, end, result.begin() + points[i]);
	}
	return result;
}
