#include "FastqReader.h"
#include <iostream>
#include <algorithm>
#include "Stella.h"
using namespace std;

FastqReader::FastqReader()
{
    current_read_ = nullptr;
    fastq_input_ = nullptr;
    tmp_read_name_ = nullptr;
    tmp_genome_sequence_ = nullptr;
    tmp_qual_sequence_ = nullptr;
}


FastqReader::~FastqReader()
{
}

void FastqReader::Init()
{
    current_read_ = new BasePairSequence();
    current_read_->Init();
    fastq_input_ = nullptr;
}

void FastqReader::SetData(void * data)
{
    if (nullptr != fastq_input_)
    {    
        fastq_input_ = nullptr;
    }
    errno_t error_num = fopen_s(&fastq_input_, static_cast<char*>(data), "r");
    if (0 != error_num)
    {
        //TODO 
    }

}

void FastqReader::GetCount()
{
}

// fopen_s() method
// SetData() method
BasePairSequence * FastqReader::Next()
{
    GetOneRead();
    ShapeAndClean();
    UpdateCurrentRead();

    return current_read_;
    // correct the read counting
    //if (read.size() >= this->minimun_read_len) this->c_total_read++;    
}

void FastqReader::ToUpperCase()
{
    std::transform((*tmp_genome_sequence_).begin(),
        (*tmp_genome_sequence_).end(),
        (*tmp_genome_sequence_).begin(),
        ::toupper);
}

void FastqReader::TrimByQuality()
{
    int end = (*tmp_qual_sequence_).size() - 1;
    for (; end >= 1; end--)
    {
        if ((*tmp_qual_sequence_)[end] > QUAL_CUTOFF
            && (*tmp_qual_sequence_)[end - 1] > QUAL_CUTOFF)
        {
            (*tmp_qual_sequence_) = (*tmp_qual_sequence_).substr(0, end);
            (*tmp_genome_sequence_) = (*tmp_genome_sequence_).substr(0, end);
            break;
        }
    }
    if (end <= 1) {
        end = 1;
        (*tmp_qual_sequence_) = (*tmp_qual_sequence_).substr(0, end);
        (*tmp_genome_sequence_) = (*tmp_genome_sequence_).substr(0, end);
    }

    int beg = 1;
    for (; beg <= (*tmp_qual_sequence_).size() - 1; beg++) {
        if ((*tmp_qual_sequence_)[beg] > QUAL_CUTOFF
            && (*tmp_qual_sequence_)[beg + 1] > QUAL_CUTOFF) {
            (*tmp_qual_sequence_) = (*tmp_qual_sequence_).substr(beg, (*tmp_qual_sequence_).size() - beg);
            (*tmp_genome_sequence_) = (*tmp_genome_sequence_).substr(beg, (*tmp_genome_sequence_).size() - beg);
            break;
        }
    }
}

void FastqReader::GetOneRead()
{
    if (nullptr == fastq_input_)
        return;

    // iterate on every line, alloc some buffer before doing alignment
    string * line;

    char buffer[2000];

    //get 4 lines of a read
    for (int lc = 0; lc < 4; lc++)
    {
        //no more data in file
        if (nullptr == fgets(buffer, 1999, fastq_input_))
        {
            break;
        }
        //get the line
        line = new string(buffer);
        //line = string(buffer);

        // skip empty lines, would not be one in common
        if ('\n' == (*line)[0] || '\r' == (*line)[0])
        {
            lc--;
            continue;
        }

        // remove blanks
        (*line).erase(std::remove((*line).begin(), (*line).end(), '\n'), (*line).end());
        (*line).erase(std::remove((*line).begin(), (*line).end(), '\r'), (*line).end());
        (*line).erase(std::remove((*line).begin(), (*line).end(), ' '), (*line).end());

        // fastq format, 0: read name, 1: read seq, 2: read name, 3: quals
        if (((lc) % 4) == 0)
        {
            //current_read_->set_read_name(line);
            tmp_read_name_ = line;
        }

        if (((lc) % 4) == 1)
        {
            //current_read_->set_original_basepair(line);
            tmp_genome_sequence_ = line;
        }
        if (((lc) % 4) == 3)
        {
            //current_read_->set_qual(line);
            tmp_qual_sequence_ = line;
        }

    }
}

void FastqReader::ShapeAndClean()
{
    ToUpperCase();
    TrimByQuality();
}

void FastqReader::UpdateCurrentRead()
{
    current_read_->Reset();
    current_read_->set_original_basepair(tmp_genome_sequence_);
    current_read_->set_qual(tmp_qual_sequence_);
    current_read_->set_read_name(tmp_read_name_);
}



