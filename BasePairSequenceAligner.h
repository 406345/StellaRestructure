// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_BASE_PAIR_ALIGNER_H_
#define STELLA_BASE_PAIR_ALIGNER_H_

#include "Stella.h"
#include "BasePairSequence.h"
#include "SharedGenedata.h"

// manage the main pipeline for an analysis of a basepair
// sequence,which means search for the position the may
// matched in a ref-genome such as hg19.fa, and
// ????
// dterming the differences 
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