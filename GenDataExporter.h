#ifndef STELLA_GEN_DATA_EXPORTER_H_
#define STELLA_GEN_DATA_EXPORTER_H_

#include "stella.h"

class GenDataExporter
{
public:
	GenDataExporter();
	~GenDataExporter();

	void ExportBasePairData(char* file_name, void* data);
	void ExportDuplicate(char* file_name, void* data);
};

#endif //STELLA_GEN_DATA_EXPORTER_H_