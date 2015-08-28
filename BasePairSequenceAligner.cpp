#include "BasePairSequenceAligner.h"

#include <string>

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

    for each (auto& kvp in search_result_)
    {
        const char* head = this->gen_data_->standard_gen() + kvp.first;
        const char* tail = this->gen_data_->standard_gen() + kvp.first + MAX_BP_LEN;

        string ori_seq(head, tail - head);
        string bp_seq(static_cast<const char*>(bp_seq_->original_basepair()), bp_seq_->original_basepair_size());

        // Diff two string with NeedlemanWunsch(dynamic programming)
        auto result = detector.NeedlemanWunsch(ori_seq, bp_seq, seqA, seqB, seqM, OPEN_GAP, OPEN_EXTN);
    }

    return kSUCCESS;
}

AlignerResult * BasePairSequenceAligner::QueryResult()
{
    return nullptr;
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
    QuickSort(&sort_pair, 0, sort_pair.size());
    map->clear();

    for each (auto& kv in sort_pair)
    {
        map->insert(make_pair(kv.first, kv.second));
    }
}

inline void BasePairSequenceAligner::QuickSort(vector<pair<size_t, int>> * data, size_t start, size_t end)
{
    pair<size_t, int> t = (*data)[start];//�ڱ���Ϊ��ͷ���Ǹ� 
    size_t f = start + 1;
    size_t b = end; //fΪǰ��ָ�룬��s+1��ʼ��bΪ����ָ�룬��e��ʼ 
    pair<size_t, int> m;
    if (start >= end)return;//�˳����� 

    while (f <= b)
    {
        while (f <= b && (*data)[f].second <= t.second) f++;    //��ǰ���ұ��ڱ����Ԫ�� 
        while (f <= b && (*data)[b].second >= t.second) b--;    //�ں����ұ��ڱ�С��Ԫ�� 
                                            //����������Ԫ�� 
        if (f<b) {
            m = (*data)[f];
            (*data)[f] = (*data)[b];
            (*data)[b] = m;
            f++;
            b--;
        }
    }
    //�����ڱ���r[b],r[b]�϶�Ҫ���ڱ�С 
    (*data)[start] = (*data)[b];
    (*data)[b] = t;
    //�����ߵ� 
    QuickSort(data, start, b - 1);
    QuickSort(data, b + 1, end);
}
 