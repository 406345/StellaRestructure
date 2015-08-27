// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_BASE_PAIR_H_
#define STELLA_BASE_PAIR_H_

#include "stella.h"

// BasePairSequence is the genome sequence and its quality 
// from a read in fastq file. It should be loaded by some 
// implements of IDataReader,the FastqReader for example,
// and the transform works like reshaping and cleaning data
// should be done by thus implements.
class BasePairSequence
{
public:
	
	// allocate sapce for genome sequences
	BasePairSequence();
	
	~BasePairSequence();
	
	// TODO non-trivial varialbes  
	void Init();
	
	//generates the sequence for the complementary strand
	void ReverseComplement();
	  
	//sequence for quality
	void* qual;
	
	//sequence based on As, Cs, Gs, Ts and Ns
	void* original_basepair;

	size_t original_basepair_size;

	//compressed in the same way to Hash table
	unsigned int * codes;

	size_t codes_size;
};

#endif //STELLA_BASE_PAIR_H_