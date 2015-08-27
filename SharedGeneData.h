#ifndef STELLA_SHARED_GEN_DATA_H_
#define STELLA_SHARED_GEN_DATA_H_

#include "stella.h"

class SharedGeneData
{
public:
    char const * standard_gen() { return standard_gen_; }
	size_t standard_gen_size() { return standard_gen_size_; }
	BasePairIndex ** base_pair_index() { return base_pair_index_; }
	size_t base_pair_index_size() { return base_pair_index_size_; }
	unsigned int const * duplicates() { return duplicates_; }
	size_t duplicates_size() { return duplicates_size_; };

	~SharedGeneData();
	 
	void Load(size_t genome_size, void* original_genome, size_t base_pair_size, void* base_pair, size_t duplicate_size, void* duplicate);
	void LoadFromFile(char* genome_file,char* base_pair_file,char* duplicate_file);

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

	char* standard_gen_;
	size_t standard_gen_size_;
	BasePairIndex** base_pair_index_;
	size_t base_pair_index_size_;
	unsigned int* duplicates_;
	size_t duplicates_size_;
};

#endif //STELLA_SHARED_GEN_DATA_H_
