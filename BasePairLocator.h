#ifndef BASE_PAIR_LOCATOR_H_
#define BASE_PAIR_LOCATOR_H_

#include "stella.h"
#include "sharedgendata.h"

class BasePairLocator
{
public:
	BasePairLocator();
	~BasePairLocator();

	void SetData(SharedGenData* data);
	BasePairIndex* Search(unsigned code);
};

#endif //BASE_PAIR_LOCATOR_H_