#include "BasePairSequence.h"
#include <string>
#include "Stella.h"
#include "BasePairCodeSample.h"

using namespace std;

//TODO describe the tricks or step for the fulfillment of the need in header file
BasePairSequence::BasePairSequence()
{
}


BasePairSequence::~BasePairSequence()
{
    delete original_basepair_;
    delete qual_;
}


void BasePairSequence::Init()
{
    read_name_ = nullptr;
    original_basepair_ = nullptr;
    qual_ = nullptr;    
    codes_ = nullptr;

    original_basepair_size_ = 0;
    codes_len_ = 0;
}

void BasePairSequence::Reset()
{
    SAFE_DELETE(read_name_);
    SAFE_DELETE(original_basepair_);
    SAFE_DELETE(qual_);
    SAFE_DELETE(codes_);
    original_basepair_size_ = 0;
    codes_len_ = 0;
}

void BasePairSequence::ReverseComplement()
{
}

HResult BasePairSequence::ReadCode(BasePairCodeSample * CurrentCodes)
{
    this->codes_len_ = this->original_basepair_size_ / MAX_BP_LEN;
    this->codes_ = new unsigned int[this->codes_len_];
    
    //TODO make the codes base on the genome sequence
    CurrentCodes->SetData(this->codes_, codes_len_, offset_);

    return HResult::kSUCCESS;
}
