#ifndef STELLA_BASE_PAIR_H_
#define STELLA_BASE_PAIR_H_

#include "stella.h"

class BasePair
{
public:
	void* qual;
	void* original_basepair;
	size_t original_basepair_size;
	unsigned int * codes;
	size_t codes_size;

	BasePair();
	~BasePair();

	void Reverse();
};

#endif //STELLA_BASE_PAIR_H_