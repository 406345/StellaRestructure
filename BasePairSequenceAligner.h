#ifndef STELLA_BASE_PAIR_ALIGNER_H_
#define STELLA_BASE_PAIR_ALIGNER_H_

#include "Stella.h"
#include "BasePairSequence.h"
#include "SharedGenedata.h"

class BasePairSequenceAligner
{
public:
	BasePairSequenceAligner();
	~BasePairSequenceAligner();

	void SetData(BasePairSequence* base_pair, SharedGeneData* gen_data);
	HResult Search();
	HResult Filter();
	HResult Diff();
	AlignerResult* QueryResult();
};

#endif //STELLA_BASE_PAIR_ALIGNER_H_