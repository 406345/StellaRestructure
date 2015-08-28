// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_FASTQ_READER_H_
#define STELLA_FASTQ_READER_H_

#include "IDataReader.h"
#include <iostream>

// Implement the IDataReader to fetch the genome reads data
// one(4 lines for certern) by one from a fastq file 
// and do the data cleaning work
class FastqReader : public IDataReader
{
public:

    FastqReader();
    ~FastqReader();

    //Inherits from IDataReader
    virtual void Init() override;
    virtual void SetData(void * data) override;
    virtual void GetCount() override;
    virtual BasePairSequence * Next() override;

private:

    // Makes all As, Cs, Gs, Ts and Ns to upper case 
    void ToUpperCase();

    // Cuts less Quality head and tail sequence off by a threshold
    void TrimByQuality();

    // Gets genome reads(4 useable lines) from the .fastq file
    void GetOneRead();
    
    // Manages the operations and their order for process the sequence
    void ShapeAndClean();

    // Make a brand new BasePairSequence directly
    void GenerateCurrentRead();

    FILE * fastq_input_;

    BasePairSequence * current_read_;
    string * tmp_read_name_;
    string * tmp_genome_sequence_;
    string * tmp_qual_sequence_;

};
#endif