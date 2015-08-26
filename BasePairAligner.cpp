#include "BasePairAligner.h"



BasePairAligner::BasePairAligner()
{
}


BasePairAligner::~BasePairAligner()
{
}

void BasePairAligner::SetData(BasePair * base_pair, SharedGenData * gen_data)
{
}

HResult BasePairAligner::Search()
{
	return HResult();
}

HResult BasePairAligner::Filter()
{
	return HResult();
}

HResult BasePairAligner::Diff()
{
	return HResult();
}

AlignerResult * BasePairAligner::QueryResult()
{
	return nullptr;
}
