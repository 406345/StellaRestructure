#include "BasePairSequence.h"
#include <string>
#include "Stella.h"
#include "BasePairCodeSample.h"

using namespace std;

BasePairSequence::BasePairSequence()
{

}

BasePairSequence::~BasePairSequence()
{
    Reset();
}


void BasePairSequence::Init()
{
    read_name_ = nullptr;
    original_basepair_ = nullptr;
    qual_ = nullptr;    
    codes_ = nullptr;

    original_basepair_size_ = 0;
    codes_len_ = 0;
    offset_ = 0;
}

void BasePairSequence::Reset()
{
    SAFE_DELETE(read_name_);
    SAFE_DELETE(original_basepair_);
    SAFE_DELETE(qual_);
    SAFE_DELETE(codes_);
    original_basepair_size_ = 0;
    codes_len_ = 0;
    offset_ = 0;
}

void BasePairSequence::ReverseComplement()
{
}

HResult BasePairSequence::ReadCode(BasePairCodeSample * CurrentCodes)
{
    if ( original_basepair_size_ < 
             offset_ + MAX_BP_LEN * (this->original_basepair_size_ / MAX_BP_LEN)
       )
    {
        return HResult::kFAIL;
    }
    
    this->codes_len_ = this->original_basepair_size_ / MAX_BP_LEN;
    this->codes_ = new unsigned int[this->codes_len_];

    // Makes the codes base on the genome sequence
    int codes_i = 0;
    int code_basepair_num = 0;
    codes_[codes_i] = 0;
    string * squence = static_cast<string *> (original_basepair_);

    for (size_t i = offset_; i < original_basepair_size_; i++)
    {
        codes_[codes_i] += BitCodes[(*squence)[i] - 'A'] << (code_basepair_num * CODE_LEN);
        if (code_basepair_num == MAX_BP_LEN)
        {
            codes_i++;
            codes_[codes_i] = 0;
            code_basepair_num = 0;
        }
    }
    
    //TODO make the codes base on the genome sequence
    CurrentCodes->SetData(this->codes_, codes_len_, offset_);
    offset_++;

    return HResult::kSUCCESS;
}
