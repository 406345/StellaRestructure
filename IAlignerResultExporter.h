#ifndef STELLA_IALIGNER_RESULT_EXPORTER_H_
#define STELLA_IALIGNER_RESULT_EXPORTER_H_

#include "Stella.h"
 
class IAlignerResultExporter
{
public:
	virtual void SetData(AlignerResult* result) = 0;
	virtual void Export() = 0;
};

#endif //STELLA_IALIGNER_RESULT_EXPORTER_H_