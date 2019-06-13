/* (c) 2019 ukrkyi */
#ifndef GENETIC_DEF_H
#define GENETIC_DEF_H

#include <vector>
#include <cinttypes>

typedef double fitness_measure;
typedef uint64_t genome_type;

#define MAX_VALUE UINT64_MAX

typedef std::pair<std::vector<bool>, fitness_measure> individual;

#endif // GENETIC_DEF_H
