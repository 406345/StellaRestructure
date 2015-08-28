#include "BasePairSequenceAligner.h"

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
    // Keep the count, to speed up
    auto bp_seq_size = this->bp_seq_->codes_size();
    for (size_t i = 0; i < bp_seq_size; i++)
    {
        auto code = this->bp_seq_->codes()[i];
        auto ret = this->locator_->Search(code);
    }
    
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
