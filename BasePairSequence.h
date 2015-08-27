#ifndef STELLA_BASE_PAIR_H_
#define STELLA_BASE_PAIR_H_

#include "stella.h"

//TODO describes what it is for and how it should be used
//genome sequence and its quality from a read in fastq file

class BasePairSequence
{
public:
	//TODO whether get onwership from somewhere else
	//TODO whether dynamic memory allocated
	BasePairSequence();
	
	//TODO whether to manage any move or delete operations
	~BasePairSequence();
	
	//TODO 
	void Init();
	
	//TODO do you mean get the reverse complements sequence as mapping phase1.2
	//make the sequence of the complementary strand
	void ReverseComplement();
	
	//removes the blanks, or any '\n', '\r'
	void CleanUpTokens();

	//makes all As, Cs, Gs, Ts and Ns to upper case 
	void ToUpperCase();

	//Cuts less Quality head and tail sequence off by a threshold
	//TODO add a file for const variables such as this threshold
	void TrimByQuality();

	// Manages the operations and their order for process the sequence
	void ShapeAndClean();
	  
	//sequence for quality
	void* qual;
	
	//sequence based on As, Cs, Gs, Ts and Ns
	void* original_basepair;

	size_t original_basepair_size;

	unsigned int * codes;

	size_t codes_size;
};

#endif //STELLA_BASE_PAIR_H_