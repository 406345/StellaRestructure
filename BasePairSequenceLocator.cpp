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
	tail_ = static_cast<int>(geneData_->base_pair_index_size()) / sizeof(BasePairIndex);
	cur_ = tail_ >> 1;

	do
	{
		//gets the pointer from the shared memory
		auto p = geneData_->base_pair_index()[cur_ * sizeof(BasePairIndex)];
		//finds it and return the result
		if (code == p->code) {
			return p;
		}
		//result maybe on the right leaf
		//find it
		else if(code > p->code){
			//(tail_ - cur_) / 2
			cur_ += ((tail_ - cur_) >> 1);
		}
		//result maybe on the left leaf
		//find it
		else {
			tail_ = cur_;
			//cur_ / 2
			cur_ = cur_ >> 1;
		}
	} 
	while (cur_>0 && cur_ != tail_ && cur_ !=(tail_ - 1));
	
	return nullptr;
}
