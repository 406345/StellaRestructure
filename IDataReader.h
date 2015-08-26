#ifndef STELLA_IDATA_READER_H_
#define STELLA_IDATA_READER_H_

#include "Stella.h"
#include "BasePair.h"

class IDataReader {
public:
	virtual void Init() = 0;
	virtual void SetData(void* data) = 0;
	virtual void GetCount() = 0;
	virtual BasePair* Next() = 0;
};

#endif //STELLA_IDATA_READER_H_