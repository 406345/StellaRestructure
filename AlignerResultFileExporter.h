// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  Exporter Class for Aligner reasult
// Creator: Shubo Yang
// Date: 2015/08/27
// Modified by Ke Yang 2015/08/28

#ifndef STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_
#define STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_

#include "IAlignerResultExporter.h"

// Aligner result is the target result stella is running
// for, this class get AlignerResult and Export it in a
// friendly format to the end-user
class AlignerResultFileExporter : public IAlignerResultExporter
{
public:

    AlignerResultFileExporter();
    ~AlignerResultFileExporter();

    // Inherit from IAlignerResultExporter
    virtual void SetData(AlignerResult * result) override;
    virtual void Export() override;
private:

    AlignerResult * export_data_;
};

#endif //STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_