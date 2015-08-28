// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  class for genome sequence from fastq file
#ifndef STELLA_BASE_PAIR_H_
#define STELLA_BASE_PAIR_H_

#include <string>
using namespace std;

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

    // Releases memory and make the BasePairSequence Init again
    void Reset();

    // Generates the sequence for the complementary strand
    void ReverseComplement();
    
    // Accessor for genome read name
    void const* read_name() 
    { 
        return read_name_;
    }

    // Mutators for genome read name
    void set_read_name(string * readname)
    {
        read_name_ = readname;
    }

    // Accessor for sequence for quality 
    void const* qual() 
    { 
        return qual_; 
    }

    // Mutators for genome read name
    void set_qual(string * qualseq)
    {
        qual_ = qualseq;
    }

    // Accessor for sequence based on As, Cs, Gs, Ts and Ns
    void const* original_basepair() 
    { 
        return original_basepair_; 
    }

    // Mutators for genome sequence 
    void set_original_basepair(string * read)
    {
        original_basepair_ = read;
    }

    size_t original_basepair_size() { return original_basepair_size_; }

    // Accessor compressed code in the same way of Compressed ref-genome
    unsigned int const* codes() { return codes_; }
    size_t codes_size(){ return codes_size_; }

private:

    // Sequence for quality
    void* qual_;

    // Sequence based on As, Cs, Gs, Ts and Ns
    void* original_basepair_;

    //Name of the genome reads
    void* read_name_;

    size_t original_basepair_size_;

    //compressed in the same way to Hash table
    unsigned int * codes_;

    size_t codes_size_;
};

#endif //STELLA_BASE_PAIR_H_