// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  class for genome sequence from fastq file
#ifndef STELLA_BASE_PAIR_H_
#define STELLA_BASE_PAIR_H_

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
	
	//getter for sequence for quality 
	void const* qual() { return qual_; }
	
	//getter for sequence based on As, Cs, Gs, Ts and Ns
	void const* original_basepair() { return original_basepair_; }
	size_t original_basepair_size() { return original_basepair_size_; }
	
	//getter for compressed in the same way to Hash table
	unsigned int const* codes() { return codes_; }
	size_t codes_size(){ return codes_size_; }

private:

	//sequence for quality
	void* qual_;

	//sequence based on As, Cs, Gs, Ts and Ns
	void* original_basepair_;

	size_t original_basepair_size_;

	//compressed in the same way to Hash table
	unsigned int * codes_;

	size_t codes_size_;
};

#endif //STELLA_BASE_PAIR_H_