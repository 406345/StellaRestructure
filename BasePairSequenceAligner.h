// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description: Manage Aligner actions 
// Creator: Shubo Yang
// Date: 2015/08/27 

#ifndef STELLA_BASE_PAIR_ALIGNER_H_
#define STELLA_BASE_PAIR_ALIGNER_H_

#include <map>
#include <vector>

#include "Stella.h"
#include "BasePairSequence.h"
#include "SharedGenedata.h"
#include "BasePairSequenceLocator.h"

// manage the main pipeline for an analysis of a basepair
// sequence,which means search for the position the may
// matched in a ref-genome such as hg19.fa, abandon
// postions with less possibility ,and then measure 
// the differences 
class BasePairSequenceAligner
{
public:

    BasePairSequenceAligner();
    ~BasePairSequenceAligner();

    void SetData(BasePairSequence* base_pair, SharedGeneData* gen_data);
    HResult Search();
    HResult Filter();
    HResult Diff();
    AlignerResult* QueryResult();

private:

    BasePairSequence* bp_seq_;
    SharedGeneData* gen_data_;
    BasePairSequenceLocator* locator_;
    map<size_t, int> search_result_;
    vector<DiffResult*> diff_result_;

    void SearchSingleSequence(BasePairSequence* seq, map<size_t, int> * map);
    void DiffSingleSequence(size_t offset, pair<size_t, int> kvp, DiffResult* result);

    int ScoreDiff(DiffResult* diff);
};

#endif //STELLA_BASE_PAIR_ALIGNER_H_