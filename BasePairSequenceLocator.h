#ifndef BASE_PAIR_LOCATOR_H_
#define BASE_PAIR_LOCATOR_H_

#include "Stella.h"
#include "SharedGeneData.h"

class BasePairSequenceLocator
{
public:
	BasePairSequenceLocator();
	~BasePairSequenceLocator();

	void SetData(SharedGeneData* data);
	BasePairIndex* Search(unsigned code);
};

#endif //BASE_PAIR_LOCATOR_H_