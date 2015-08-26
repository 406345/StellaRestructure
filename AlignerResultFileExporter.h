#ifndef STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_
#define STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_

#include "IAlignerResultExporter.h"
class AlignerResultFileExporter : public IAlignerResultExporter
{
public:
	AlignerResultFileExporter();
	~AlignerResultFileExporter();

	// Í¨¹ý IAlignerResultExporter ¼Ì³Ð
	virtual void SetData(AlignerResult * result) override;
	virtual void Export() override;
};

#endif //STELLA_ALIGNER_RESULT_FILE_EXPORTER_H_