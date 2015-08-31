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
    this->bp_seq_ = base_pair;
    this->gen_data_ = gen_data;

    this->locator_->SetData(gen_data);
}

// Search all possible hit positions
HResult BasePairSequenceAligner::Search()
{
    if (nullptr == this->bp_seq_) return kFAIL;

    if (nullptr == this->gen_data_) return kFAIL;

    this->SearchSingleSequence(this->bp_seq_, &search_result_);

    if (0 == search_result_.size())return kFAIL;

    return kSUCCESS;
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

            // Find the hit of code
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
    for (size_t i = sort_pair_size; i > 0; i--)
    {
        if (sort_pair[i].second == 1) {
            sort_pair.erase(sort_pair.begin() + i);
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

// Remove useless( hit count != max_count)
HResult BasePairSequenceAligner::Filter()
{
    if (search_result_.size() == 0)
		return kFAIL;

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

    for each (auto& kvp in search_result_)
    {
        DiffResult* result = new DiffResult();
        memset(result, 0, sizeof(DiffResult));
        result->diff_score = -INT_MAX;

        size_t count = this->bp_seq_->max_code_len() > kvp.second ? this->bp_seq_->max_code_len() - kvp.second : 0;
        for (size_t code_begin_pos = 0; code_begin_pos <= count; code_begin_pos++)
        {
            // Different is at the front of the code position
            size_t offset = kvp.first - MAX_BP_LEN * (code_begin_pos);

            DiffResult result_front, result_back;

            DiffSingleSequence(offset, kvp, &result_front);

            ScoreDiff(&result_front);

            // Select the higher score 
            auto higher_result = result_front;

            if (result->diff_score < higher_result.diff_score)
            {
                result->diff = string(higher_result.diff);
                result->diff_score = higher_result.diff_score;
                result->hit_sequence = string(higher_result.hit_sequence);
                result->original_sequence = string(higher_result.original_sequence);
                result->position = higher_result.position;
                result->original_sequence_trans = string(higher_result.original_sequence_trans);
                result->hit_sequence_trans = string(higher_result.hit_sequence_trans);
            }
        }

        diff_result_.push_back(result);
    }

    return kSUCCESS;
}

void BasePairSequenceAligner::DiffSingleSequence(size_t offset, pair<size_t, int> kvp, DiffResult* result)
{
    BasePairSequenceDifferencesDetector detector;
    string seqA, seqB, seqM;

    size_t head_offset = offset;

    if (head_offset < 0) head_offset = 0;

    const char* head = this->gen_data_->standard_gen() + head_offset;

    size_t size = bp_seq_->original_basepair_size();

    if ((head_offset + size) > this->gen_data_->standard_gen_size()) size = this->gen_data_->standard_gen_size() - head_offset;

    string ori_seq;

    size_t end = size;
    for (size_t i = 0; i < end; i++)
    {
        char c = *(head + i);

        if (c == '\n')
        {
            end++;
        }
        else
        {
            ori_seq += c;
        }
    }

    string bp_seq = "*" + *((string*)bp_seq_->original_basepair());

    ori_seq = "*" + ori_seq;

    // Diff two string with NeedlemanWunsch(dynamic programming)
    detector.NeedlemanWunsch(ori_seq, bp_seq, seqA, seqB, seqM, OPEN_GAP, OPEN_EXTN);

    result->original_sequence = string(ori_seq);
    result->original_sequence_trans = string(seqA);
    result->hit_sequence = string(bp_seq);
    result->hit_sequence_trans = string(seqB.substr(0, size));
    result->diff = string(seqM.substr(0, size));
    result->position = offset;

}

int BasePairSequenceAligner::ScoreDiff(DiffResult* diff)
{
    int score = 0;

    for (size_t i = 0; diff->diff[i] != '\0'; i++)
    {
        if (diff->diff[i] == SCORE_SAME_LETTER)
        {
            score++;
        }
        else
        {
            score--;
        }
    }

    diff->diff_score = score;

    return score;
}

AlignerResult * BasePairSequenceAligner::QueryResult()
{
    for each (auto& item in diff_result_)
    {
        printf_s("///////////////////////////////////////////////////////////////\r\n");
        printf_s("Orignal Sequence: %s\r\n", item->original_sequence.c_str() + 1);
        printf_s("Hit Sequence:     %s\r\n", item->hit_sequence.c_str() + 1);
        printf_s("Hit Patch:        %s\r\n", item->hit_sequence_trans.c_str());
        printf_s("Difference:       %s\r\n", item->diff.c_str());
        printf_s("Score:            %d\r\n", item->diff_score);
        printf_s("Position:         %lld\r\n", item->position);
    }
    return nullptr;
}

