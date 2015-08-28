#include "BasePairSequenceLocator.h"

BasePairSequenceLocator::BasePairSequenceLocator()
{
    
}

BasePairSequenceLocator::~BasePairSequenceLocator()
{

}

void BasePairSequenceLocator::SetData(SharedGeneData * data)
{
    geneData_ = data;
}

BasePairIndex * BasePairSequenceLocator::Search(unsigned code)
{
    tail_ = static_cast<size_t>(geneData_->base_pair_index_size());
    cur_ = tail_ >> 1;

    while (cur_ != tail_)
    {
        // Gets the pointer from the shared memory
        auto p = (geneData_->base_pair_index()+ cur_);
        
        // Check code and return the result
        if (code == p->code) 
        {
            return p;
        }
        
        // The result maybe on the right leaf
        // Find it
        else if(code > p->code)
        {
            //(tail_ - cur_) / 2
            cur_ += ((tail_ - cur_ + 1) >> 1);
        }
        
        // The result maybe on the left leaf, find it
        else 
        {
            tail_ = cur_;
            // cur_ / 2
            cur_ = cur_ >> 1;
        }
    } 
    
    return nullptr;
}
