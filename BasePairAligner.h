#ifndef STELLA_BASE_PAIR_ALIGNER_H_
#define STELLA_BASE_PAIR_ALIGNER_H_

#include "stella.h"
#include "basepair.h"
#include "sharedgendata.h"

class BasePairAligner
{
public:
	BasePairAligner();
	~BasePairAligner();

	void SetData(BasePair* base_pair, SharedGenData* gen_data);
	HResult Search();
	HResult Filter();
	HResult Diff();
	AlignerResult* QueryResult();
};

#endif //STELLA_BASE_PAIR_ALIGNER_H_