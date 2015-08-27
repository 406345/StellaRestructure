#pragma once
#include "IDataReader.h"
class FastqReader : public IDataReader
{
public:
	FastqReader();
	~FastqReader();

	//inherit from IDataReader
	virtual void Init() override;
	virtual void SetData(void * data) override;
	virtual void GetCount() override;
	virtual BasePairSequence * Next() override;
private:

};

