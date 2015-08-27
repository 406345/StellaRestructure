// Copyright (c) 2015 Yhgenomics. All rights reserved.
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

	// inherit from IAlignerResultExporter
	virtual void SetData(AlignerResult * result) override;
	virtual void Export() override;
};

#endif //STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_