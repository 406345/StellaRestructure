// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_FASTQ_READER_H_
#define STELLA_FASTQ_READER_H_

#include "IDataReader.h"

// implement the IDataReader to fetch the genome reads data
// one(4 lines for certern) by one from a fastq file 
// and do the data cleaning work
class FastqReader : public IDataReader
{
public:

	FastqReader();
	~FastqReader();

	//inherit from IDataReader
	virtual void Init() override;
	virtual void SetData(void * data) override;
	virtual void GetCount() override;
	virtual BasePairSequence * Next() override;

private:

	//removes the blanks, or any '\n', '\r'
	void CleanUpTokens();

	//makes all As, Cs, Gs, Ts and Ns to upper case 
	void ToUpperCase();

	//Cuts less Quality head and tail sequence off by a threshold
	//TODO add a file for const variables such as this threshold
	void TrimByQuality();

	// Manages the operations and their order for process the sequence
	void ShapeAndClean();

};
#endif