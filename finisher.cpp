/* (c) 2019 ukrkyi */
#include "finisher.h"

IterationFinisher::IterationFinisher(size_t number)
	: iteration_number(number), current_iteration(0) {}

void IterationFinisher::start()
{
	current_iteration = 0;
}

bool IterationFinisher::is_finish(std::vector<individual> &)
{
	current_iteration++;
	return current_iteration > iteration_number;
}
