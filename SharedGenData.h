#ifndef STELLA_SHARED_GEN_DATA_H_
#define STELLA_SHARED_GEN_DATA_H_

#include "stella.h"

class SharedGenData
{
public:
	char* standard_gen;
	size_t standard_gen_size;
	BasePairIndex* base_pair_index;
	size_t base_pair_index_size;
	unsigned int* duplicates;
	size_t duplicates_size;

	~SharedGenData();
	 
	void Load(void* original_genome, void* base_pair, void* duplicate);

	static SharedGenData* instance()
	{
		if (!instance_)
		{
			instance_ = new SharedGenData();
		}
		return instance_;
	};
private:
	SharedGenData();

	static SharedGenData* instance_;
};

#endif //STELLA_SHARED_GEN_DATA_H_
