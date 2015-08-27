#include "BasePairSequenceAligner.h"



BasePairSequenceAligner::BasePairSequenceAligner()
{
}


BasePairSequenceAligner::~BasePairSequenceAligner()
{
}

void BasePairSequenceAligner::SetData(BasePairSequence * base_pair, SharedGeneData * gen_data)
{
}

HResult BasePairSequenceAligner::Search()
{
	return HResult();
}

HResult BasePairSequenceAligner::Filter()
{
	return HResult();
}

HResult BasePairSequenceAligner::Diff()
{
	return HResult();
}

AlignerResult * BasePairSequenceAligner::QueryResult()
{
	return nullptr;
}
