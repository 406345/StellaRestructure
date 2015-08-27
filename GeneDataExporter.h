// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_GEN_DATA_EXPORTER_H_
#define STELLA_GEN_DATA_EXPORTER_H_

#include "stella.h"

// Export the basepair data and duplicate
class GeneDataExporter
{
public:

	GeneDataExporter();
	~GeneDataExporter();

	void ExportBasePairData(const char* file_name, void* data);
	void ExportDuplicate(const char* file_name, void* data);
};

#endif //STELLA_GEN_DATA_EXPORTER_H_