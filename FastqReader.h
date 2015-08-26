#pragma once
#include "IDataReader.h"
class FastqReader : public IDataReader
{
public:
	FastqReader();
	~FastqReader();

	// Í¨¹ý IDataReader ¼Ì³Ð
	virtual void Init() override;
	virtual void SetData(void * data) override;
	virtual void GetCount() override;
	virtual BasePair * Next() override;
};

