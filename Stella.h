// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  configuration file for global variables
#ifndef STELLA_STELLA_H_
#define STELLA_STELLA_H_

#define SAFE_DELETE(__x__) if(__x__ != nullptr) delete __x__

const int MAX_BP_LINE_LENGTH = 300;
const int MAX_BP_LEN = 10;

enum HResult
{
	kSUCCESS = 0,
	kFAIL
};

struct BasePairIndex
{
	unsigned int code;
	size_t offset;
	size_t count;
};

struct BasePairDiffMaker
{
	unsigned long ref_pos;
	char original_base_pair;
	char current_base_pair;
	char different;
};

struct AlignerResult {
	BasePairDiffMaker* base_pair_diff_maker;
	size_t diff_size;
	BasePairIndex* base_pair_index;
};

const unsigned int BitCodes[60] = \
	/* A   B   C    D  E, F, G    H   I   J  K  L  M  N  O  P  Q  R  S  T    U  V  W  X  Y  Z */ \
	{0b00, 0, 0b01, 0, 0, 0, 0b10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b11, 0, 0, 0, 0, 0, 0,
	/*  [  \  ]  ^  _  `  */
	0, 0, 0, 0, 0, 0,
	/* a   b   c    d  e, f, g    h   i   j  k  l  m  n  o  p  q  r  s  t    u  v  w  x  y  z */
	0b00, 0, 0b01, 0, 0, 0, 0b10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0b11, 0, 0, 0, 0, 0, 0
};


 
#endif //STELLA_STELLA_H_