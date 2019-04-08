/* (c) 2019 ukrkyi */
#ifndef FINISHER_H
#define FINISHER_H

#include "genetic.h"

class Finisher
{
public:
	virtual void start() = 0;
	virtual bool is_finish(std::vector<individual>&) = 0;
};

class IterationFinisher : public Finisher
{
	size_t iteration_number;
	size_t current_iteration;
public:
	IterationFinisher(size_t number);
	virtual void start();
	virtual bool is_finish(std::vector<individual>&);
};

#endif // FINISHER_H
