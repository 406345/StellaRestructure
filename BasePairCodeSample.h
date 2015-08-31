// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description: The certern code for a basepari sequence by its offset. 
// Creator: Shubo Yang
// Date: 2015/08/28
// Modified by Ke Yang 2015/08/28

#ifndef STELLA_BASE_PAIR_CODE_SAMPLE_H_
#define STELLA_BASE_PAIR_CODE_SAMPLE_H_

#include "Stella.h"

class BasePairCodeSample
{
public:

    BasePairCodeSample();
    ~BasePairCodeSample();

    unsigned int const * codes() { return codes_; }
    size_t codes_len() { return codes_len_; }
    size_t offset() { return offset_; }

    void SetData(unsigned int* codes, size_t codes_len, size_t offset);

private:

    unsigned int * codes_;
    size_t codes_len_;
    size_t offset_;

};

#endif //STELLA_BASE_PAIR_CODE_SAMPLE_H_