#include "SharedGeneData.h"
#include <stdio.h>

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
	this->base_pair_index_ = static_cast<BasePairIndex**>(base_pair);

	this->duplicates_size_ = duplicate_size;
	this->duplicates_ = (unsigned int*)duplicate;
}

void SharedGeneData::LoadFromFile(const char * genome_file, const char * base_pair_file, const char * duplicate_file)
{
	FILE * file_genome, * file_bp, * file_duplicate;
	size_t genome_size, bp_size, duplicate_size;

	auto error = fopen_s(&file_genome, genome_file, "r");

	if (error) 
    { 
#ifdef DEBUG
        printf("open genome file error"); 
#endif
        return;
    }

	error = fopen_s(&file_bp, base_pair_file, "r");

	if (error) 
    { 
#ifdef DEBUG
        printf("open base pair file error");
#endif
        return; 
    }

	error = fopen_s(&file_duplicate, duplicate_file, "r");

	if (error) 
    { 
#ifdef DEBUG
        printf("open duplicate file error");
#endif
        return; 
    }

	fseek(file_genome, 0, SEEK_END);
	genome_size = static_cast<size_t>(ftell(file_genome));
	fseek(file_genome, 0, SEEK_SET);

	fread_s(&bp_size, sizeof(size_t), sizeof(size_t), 1, file_bp);
	fread_s(&duplicate_size, sizeof(size_t), sizeof(size_t), 1, file_duplicate);

	void* buf_genome = (void*) new char[genome_size]();
	fread(buf_genome, sizeof(char), genome_size, file_genome);

	void* buf_bp = (void*)new char[bp_size]();
	fread(buf_bp, sizeof(char), bp_size, file_bp);

	void* buf_duplicate = (void*)new char[duplicate_size]();
	fread(buf_bp, sizeof(char), duplicate_size, file_duplicate);

	this->Load(genome_size, buf_genome, bp_size, buf_bp, duplicate_size, buf_duplicate);
}