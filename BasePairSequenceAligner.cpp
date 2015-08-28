#include "BasePairSequenceAligner.h"
#include "BasePairCodeSample.h"

BasePairSequenceAligner::BasePairSequenceAligner()
{
    locator_ = new BasePairSequenceLocator();
}

BasePairSequenceAligner::~BasePairSequenceAligner()
{
    SAFE_DELETE(locator_);
}

void BasePairSequenceAligner::SetData(BasePairSequence * base_pair, SharedGeneData * gen_data)
{
    this->bp_seq_   = base_pair;
    this->gen_data_ = gen_data;
    this->locator_->SetData(gen_data);
}

HResult BasePairSequenceAligner::Search()
{
    BasePairCodeSample sample;
    do{

    }
    while (1);
    /*for (size_t i = 0; i < bp_seq_size; i++)
    {
        auto code = this->bp_seq_->codes()[i];
        auto ret = this->locator_->Search(code);
    }*/
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
