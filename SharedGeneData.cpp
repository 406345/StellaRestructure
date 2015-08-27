#include "SharedGeneData.h"



SharedGeneData::SharedGeneData()
{

}


SharedGeneData::~SharedGeneData()
{
}

void SharedGeneData::Load(size_t genome_size, void * original_genome, size_t base_pair_size, void * base_pair, size_t duplicate_size, void * duplicate)
{
	this->standard_gen_size_ = genome_size;
	this->standard_gen_ = static_cast<char*> (original_genome);

	

	this->base_pair_index_size_ = base_pair_size;
	this->base_pair_index_ = (BasePairIndex**)original_genome;

	this->duplicates_size_ = duplicate_size;
	this->duplicates_ = (unsigned int*)duplicate;

}

void SharedGeneData::LoadFromFile(const char * genome_file, const char * base_pair_file, const char * duplicate_file)
{

}
 