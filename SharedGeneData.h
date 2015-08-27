// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_SHARED_GEN_DATA_H_
#define STELLA_SHARED_GEN_DATA_H_

#include "stella.h"

class SharedGeneData
{
public:
	char* standard_gen;
	size_t standard_gen_size;
	BasePairIndex* base_pair_index;
	size_t base_pair_index_size;
	unsigned int* duplicates;
	size_t duplicates_size;

	~SharedGeneData();
	 
	void Load(void* original_genome, void* base_pair, void* duplicate);

	static SharedGeneData* instance()
	{
		if (!instance_)
		{
			instance_ = new SharedGeneData();
		}
		return instance_;
	};
private:
	SharedGeneData();

	static SharedGeneData* instance_;
};

#endif //STELLA_SHARED_GEN_DATA_H_
