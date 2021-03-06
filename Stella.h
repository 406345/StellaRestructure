// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  configuration file for global variables
#ifndef STELLA_STELLA_H_
#define STELLA_STELLA_H_

#include <string>

//#define DEBUG

#define SAFE_DELETE(__x__) { if((__x__) != nullptr) { delete (__x__); (__x__) = nullptr;} }
#define SAFE_DELETE_ARRAY(__x__) { if((__x__) != nullptr ){ delete[] (__x__);  (__x__) = nullptr;} }

const int MAX_BP_LINE_LENGTH = 300;
const int MAX_BP_LEN = 10;
const int CODE_LEN = 3;
const unsigned char QUAL_CUTOFF = 36;
const int MINIMUN_HIT = 1;

const int OPEN_GAP = -3;
const int OPEN_EXTN = 0;

const char SCORE_SAME_LETTER = 'M';

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

struct BasePairDiffMarker
{
    unsigned long ref_pos;
    char original_base_pair;
    char current_base_pair;
    char different;
};

struct AlignerResult {
    BasePairDiffMarker* base_pair_diff_maker;
    size_t diff_size;
    BasePairIndex* base_pair_index;
};

struct DiffResult {
    std::string original_sequence;
    std::string original_sequence_trans;
    std::string hit_sequence;
    std::string hit_sequence_trans;
    std::string diff;
    int diff_score;
    size_t position;
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