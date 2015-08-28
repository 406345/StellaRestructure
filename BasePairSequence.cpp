#include "BasePairSequence.h"
#include <string>
#include "Stella.h"

using namespace std;

//TODO describe the tricks or step for the fulfillment of the need in header file
BasePairSequence::BasePairSequence()
{
}


BasePairSequence::~BasePairSequence()
{
	delete original_basepair_;
	delete qual_;
}


void BasePairSequence::Init()
{
	read_name_ = nullptr;
	original_basepair_ = nullptr;
	qual_ = nullptr;	
	codes_ = nullptr;

	original_basepair_size_ = 0;
	codes_size_ = 0;
}

void BasePairSequence::Reset()
{
	SAFE_DELETE(read_name_);
	SAFE_DELETE(original_basepair_);
	SAFE_DELETE(qual_);
	SAFE_DELETE(codes_);
	original_basepair_size_ = 0;
	codes_size_ = 0;
}

void BasePairSequence::ReverseComplement()
{
}