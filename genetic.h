/* (c) 2019 ukrkyi */
#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <cstdint>

#include "genetic_def.h"

#include "generator.h"
#include "finisher.h"

template<typename ... Types>
class Genetic
{
	typedef fitness_measure (*fitness_function)(Types...);
	std::vector<individual> population;
	Generator& generator;
	fitness_function function;
	std::tuple<std::pair<Types, Types> ...> range;
	void (*dump_function)(Types...);
	void dump_population();
	fitness_measure fitness(std::vector<bool>&);

	std::tuple<Types...> convert(std::vector<bool>& genome);
public:
	Genetic(size_t populationSize, fitness_function f, std::tuple<std::pair<Types, Types> ...> ranges, Generator& gen);
	std::tuple<Types...> run(Finisher& condition);
	void enable_output(void (*dumper)(Types...));
};


#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <iostream>

#include <cstdint>
#include <numeric>
#include <tuple>
#include <utility>
#include <functional>

template<typename ... Types>
Genetic<Types...>::Genetic(size_t populationSize, fitness_function f, std::tuple<std::pair<Types, Types> ...> ranges, Generator& gen):
	population(populationSize, individual(std::vector<bool>(sizeof (genome_type) * 8 * sizeof... (Types)), 0)),
	generator(gen), function(f), dump_function(nullptr), range(ranges)
{
	std::srand(std::time(0));
}

template<typename ... Types>
void Genetic<Types...>::dump_population()
{
	if (dump_function != nullptr) {
		for (auto & ind : population)
			std::apply(dump_function, convert(ind.first));
		std::cout << std::endl;
	}
}

template<typename ... Types>
std::tuple<Types...> Genetic<Types...>::run(Finisher &condition)
{
	condition.start();
	generator.create_population(population, std::bind(&Genetic<Types...>::fitness, this, std::placeholders::_1));
	dump_population();
	while (!condition.is_finish(population)) {
		generator.new_generation(population, std::bind(&Genetic<Types...>::fitness, this, std::placeholders::_1));
		dump_population();
	}
	return convert(std::max_element(population.begin(), population.end(), [](individual& a, individual& b){ return a.second < b.second;})->first);
}

template<typename ... Types>
void Genetic<Types...>::enable_output(void (*dumper)(Types...))
{
	dump_function = dumper;
}

template<typename ... Types>
fitness_measure Genetic<Types...>::fitness(std::vector<bool> &genome)
{
	return std::apply(function, convert(genome));
}

template <typename T, std::size_t... Indices>
auto to_tuple(const std::vector<T>& v, std::index_sequence<Indices...>) {
  return std::make_tuple(v[Indices]...);
}

template<typename T>
T convert_element(std::vector<bool>& genome, size_t position, std::pair<T, T>& range){
	genome_type bits = std::accumulate(genome.begin() + sizeof(genome_type)*8*position, genome.begin() + sizeof(genome_type)*8*(position + 1), 0ULL, [](uint64_t x, bool y) { return (x << 1) + y; });
	return T(range.first + ((long double) bits) / MAX_VALUE * (range.second - range.first));
}

template<typename Tuple1, typename Tuple2, size_t ... I>
auto call(std::vector<bool>& genome, Tuple1 t1, Tuple2 t2, std::index_sequence<I ...>)
{
     return std::make_tuple(convert_element(genome, std::get<I>(t1), std::get<I>(t2))...);
}

template<typename ... Types>
std::tuple<Types...> Genetic<Types...>::convert(std::vector<bool>& genome)
{
	std::vector<size_t> elements(sizeof... (Types));
	std::iota(elements.begin(), elements.end(), 0);
	static constexpr auto seq = std::make_index_sequence<sizeof... (Types)>();
	return call(genome, to_tuple(elements, seq), range, seq);
}

#endif // GENETIC_H
