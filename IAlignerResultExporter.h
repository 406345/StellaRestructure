// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  Interface for aligner result exporting
// Creator: Shubo Yang
// Date: 2015/08/27 

#ifndef STELLA_IALIGNER_RESULT_EXPORTER_H_
#define STELLA_IALIGNER_RESULT_EXPORTER_H_

#include "Stella.h"

//    Result export interface
class IAlignerResultExporter
{
public:

    virtual void SetData(AlignerResult* result) = 0;
    virtual void Export() = 0;
};

#endif //STELLA_IALIGNER_RESULT_EXPORTER_H_