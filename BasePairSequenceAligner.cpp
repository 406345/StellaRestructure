#include "BasePairSequenceAligner.h"

#include <string>
#include <algorithm>
#include <functional>

#include "BasePairCodeSample.h"
#include "BasePairSequenceDifferencesDetector.h"

using namespace std;

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
    if (nullptr == this->bp_seq_) return kFAIL;

    if (nullptr == this->gen_data_) return kFAIL;

    this->SearchSingleSequence(this->bp_seq_, &search_result_);

    if (0 == search_result_.size())return kFAIL;

    return kSUCCESS;
}

HResult BasePairSequenceAligner::Filter()
{
    if (search_result_.size() == 0)return kFAIL;

    // Copy search result to a temporary array 
    vector<pair<size_t, int> > buf(search_result_.begin(), search_result_.end());

    // Max hit count is the first element
    int hit_count = search_result_.begin()->second;

    for each (auto& kv in buf)
    {
        // Pick out item which hit count less than Max hit and less than mininum hit
        if (kv.second < hit_count || kv.second <= MINIMUN_HIT) 
        {
            search_result_.erase(kv.first);
        }
    }

    return kSUCCESS;
}

HResult BasePairSequenceAligner::Diff()
{
    if (search_result_.size() == 0)return kFAIL;

    BasePairSequenceDifferencesDetector detector;
    string seqA, seqB, seqM;

    size_t code_len = (bp_seq_->original_basepair_size()) / MAX_BP_LEN;

    for each (auto& kvp in search_result_)
    {
        size_t head_offset = kvp.first - MAX_BP_LEN * (code_len - kvp.second);
        size_t tail_offset = kvp.first + MAX_BP_LEN * code_len;

        if (head_offset < 0) head_offset = 0;

        if (tail_offset > this->gen_data_->standard_gen_size()) tail_offset = this->gen_data_->standard_gen_size();

        const char* head = this->gen_data_->standard_gen() + head_offset;
        const char* tail = this->gen_data_->standard_gen() + tail_offset;
         
        size_t ori_size = tail - head + 1;
        size_t bp_size = bp_seq_->original_basepair_size();

         

        string ori_seq(head, bp_seq_->original_basepair_size());

        string new_ori_seq = ori_seq.erase('\n');

        string bp_seq = *((string*)bp_seq_->original_basepair());// (static_cast<const char*>(bp_seq_->original_basepair()), bp_seq_->original_basepair_size());

        // Diff two string with NeedlemanWunsch(dynamic programming)
        auto result = detector.NeedlemanWunsch(ori_seq, bp_seq, seqA, seqB, seqM, OPEN_GAP, OPEN_EXTN);
    }

    return kSUCCESS;
}

AlignerResult * BasePairSequenceAligner::QueryResult()
{
    return nullptr;
}


bool vector_sort(const pair<size_t, int>& m1, const pair<size_t, int>& m2)
{
    return m1.second > m2.second;;
}


void BasePairSequenceAligner::SearchSingleSequence(BasePairSequence * seq, map<size_t, int>* map)
{
    do
    {
        BasePairCodeSample sample;

        if (this->bp_seq_->ReadCode(&sample))break;

        size_t code_len = sample.codes_len();

        for (size_t i = 0; i < code_len; i++)
        {
            auto code = sample.codes()[i];

            // Find the hit of the code
            auto ret = this->locator_->Search(code);

            if (ret == nullptr)  continue;

            for (size_t j = 0; j < ret->count; j++)
            {
                auto pos = *(this->gen_data_->duplicates() + ret->offset + j);

                // Relative position to bp line's head position
                auto relPos = pos - i * MAX_BP_LEN;

                // Check if the item is already exist
               if (map->find(relPos) == map->end())
                {
                    map->insert(make_pair(relPos, 0));
                }

                (*map)[relPos] = (*map)[relPos] + 1;
            }
        } 
    } while (1);

    vector<pair<size_t, int> > sort_pair(map->begin(), map->end());
    size_t sort_pair_size = sort_pair.size() - 1;
    for (size_t i = sort_pair_size; i >0; i--)
    {
        if (sort_pair[i].second == 1) {
            sort_pair.erase(sort_pair.begin()+i);
        }
    }

    sort(sort_pair.begin(), sort_pair.end(), vector_sort);

    //QuickSort(&sort_pair, 0, sort_pair.size() - 1);
    map->clear();

    for each (auto& kv in sort_pair)
    {
        map->insert(make_pair(kv.first, kv.second));
    }
}
 
inline void BasePairSequenceAligner::QuickSort(vector<pair<size_t, int>> * data, size_t start, size_t end)
{
    pair<size_t, int> t = (*data)[start];//哨兵，为开头的那个 
    size_t f = start + 1;
    size_t b = end; //f为前向指针，从s+1开始，b为反向指针，从e开始 
    pair<size_t, int> m;
    if (start >= end)return;//退出条件 

    while (f <= b)
    {
        while (f <= b && (*data)[f].second <= t.second) f++;    //在前面找比哨兵大的元素 
        while (f <= b && (*data)[b].second >= t.second) b--;    //在后面找比哨兵小的元素 
                                            //交换这两个元素 
        if (f<b) {
            m = (*data)[f];
            (*data)[f] = (*data)[b];
            (*data)[b] = m;
            f++;
            b--;
        }
    }
    //交换哨兵和r[b],r[b]肯定要比哨兵小 
    (*data)[start] = (*data)[b];
    (*data)[b] = t;
    //排两边的 
    QuickSort(data, start, b - 1);
    QuickSort(data, b + 1, end);
}
