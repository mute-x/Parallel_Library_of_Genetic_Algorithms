/* (c) 2019 ukrkyi */
#include "generator.h"

#include "selector.h"
#include "recombinator.h"
#include "mutator.h"

#include <algorithm>
#include "tbb/tbb.h"

Generator::Generator(Selector &sel, Recombinator &rec, Mutator &m)
        : selector(sel), recombinator(rec), mutator(m) {}

void Generator::create_population(std::vector<individual> &population, fitness_function fitness) {
    // Generate random population
    for (auto &individual: population) {
        std::generate(individual.first.begin(), individual.first.end(), []() { return (bool) (std::rand() % 2); });
        individual.second = fitness(individual.first);
    }
}

void FullReplacementGenerator::new_generation(std::vector<individual> &population, fitness_function fitness) {
    std::vector<individual> old_population(population);
    selector.set_population(old_population);
    for (size_t i = 0; i < population.size(); i++) {
        std::pair<size_t, size_t> parents = selector.get_pair();
        population[i].first = mutator.mutate(recombinator.crossover(
                old_population[parents.first].first, old_population[parents.second].first));
        population[i].second = fitness(population[i].first);
    }
}

void FullReplacementGenerator::new_generation_parallel(std::vector<individual> &population, fitness_function fitness) {
    std::vector<individual> old_population(population);
    selector.set_population(old_population);
    for (size_t i = 0; i < population.size(); i++) {
        std::pair<size_t, size_t> parents = selector.get_pair();
        population[i].first = mutator.mutate(recombinator.crossover(
                old_population[parents.first].first, old_population[parents.second].first));
    }
    tbb::parallel_for(tbb::blocked_range<size_t>(0, population.size()),
                 CalculateFitness(population, fitness));

}


