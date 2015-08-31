#include "BasePairCodeSample.h"

BasePairCodeSample::BasePairCodeSample()
{
    this->codes_ = nullptr;
}

BasePairCodeSample::~BasePairCodeSample()
{
    SAFE_DELETE_ARRAY(this->codes_);
}

void BasePairCodeSample::SetData(unsigned int * codes, size_t codes_len, size_t offset)
{
    this->codes_     = codes;
    this->codes_len_ = codes_len;
    this->offset_    = offset;
}
