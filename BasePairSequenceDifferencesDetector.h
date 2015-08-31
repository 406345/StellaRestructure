// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description:  Needleman¨CWunsch algorithm
// Creator: Shubo Yang
// Date: 2015/08/27 

#ifndef STELLA_BASE_PAIR_DIFFERENCE_DETECTOR_H_
#define STELLA_BASE_PAIR_DIFFERENCE_DETECTOR_H_

#include <string>

#include "Stella.h"

using namespace std;

template<typename T> 
class matrix 
{
private:

    int dim_x = 0;
    int dim_y = 0;
    T* buf;     
    matrix(int _dimx, int _dimy)
    {
        this->dim_x = _dimx;
        this->dim_y = _dimy;
        int size = this->dim_x*this->dim_y;
        buf = (T*)malloc(size*sizeof(T));
        std::memset(buf, 0, size*sizeof(T));
    }

public:

    ~matrix() {}
    matrix() { buf = 0; }

    matrix(T* _buf) {
        this->dim_x = MAX_BP_LINE_LENGTH;
        this->dim_y = MAX_BP_LINE_LENGTH;
        buf = _buf;
    }

    // Reset the ram
    inline void clear(unsigned char _value = 0) {
        std::memset(buf, _value, this->dim_x * this->dim_y * sizeof(T));
    }

    // Return the reference of a element
    inline T& get(int _x, int _y) {
        return buf[_x * this->dim_y + _y];
    }

    inline T& operator() (const int& _x, const int& _y) {
        return buf[_x * this->dim_y + _y];
    }
};
 
// Detectes the differences of two base pair sequences
// Needleman¨CWunsch algorithm
class BasePairSequenceDifferencesDetector
{
public:

    BasePairSequenceDifferencesDetector();
    ~BasePairSequenceDifferencesDetector();

    void clear();
    int NeedlemanWunsch(
        string & f1, 
        string & f2,
        string & sequenceA,
        string & sequenceB,
        string & sequenceM,
        int gap_open,
        int gap_extn);

private:

    string seqW = "*ACGTN";    // Nucleotides
    int imut[6][6] = {
        1,0,0,0,0,0,
        0,1,0,0,0,0,
        0,0,1,0,0,0,
        0,0,0,1,0,0,
        0,0,0,0,1,0,
        0,0,0,0,0,1 };

    int* buf; // point to ram buffer
    matrix<int> score;
    matrix<int> val;
    matrix<int> idir;
    matrix<int> preV;
    matrix<int> preH;
    matrix<int> jpV;
    matrix<int> jpH;
    int seq1[MAX_BP_LINE_LENGTH];
    int seq2[MAX_BP_LINE_LENGTH];
    int j2i[MAX_BP_LINE_LENGTH]; 
};

#endif //STELLA_BASE_PAIR_DIFFERENTER_H_