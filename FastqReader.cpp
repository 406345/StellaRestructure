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
    current_read_ = nullptr;
    fastq_input_ = nullptr;
}

void FastqReader::SetData( void * data )
{
    if ( nullptr != fastq_input_ )
    {    
        fastq_input_ = nullptr;
    }

    errno_t error_num = fopen_s( &fastq_input_, static_cast<char*>(data), "r" );
    if ( 0 != error_num )
    {
        //TODO options on certern error code
    }

}

void FastqReader::GetCount()
{
}

// File lines inputs to three tmp variables.
// After data-cleaning work done, generate current_read_£¬
// and then return it
BasePairSequence * FastqReader::Next()
{
    if ( HResult::kFAIL == GetOneRead() )
    {
        return nullptr;
    }

    ShapeAndClean();
    GenerateCurrentRead();

    return current_read_;
    //TODO 
}

// Use only on  tmp_genome_sequence_
void FastqReader::ToUpperCase()
{
    std::transform( ( *tmp_genome_sequence_ ).begin(),
        ( *tmp_genome_sequence_ ).end(),
        ( *tmp_genome_sequence_ ).begin(),
        ::toupper );
}

// Trim by QUAL_CUTOFF defined in stella.h
void FastqReader::TrimByQuality()
{
    // TODO re-write this with a more expressive way
    size_t end = ( *tmp_qual_sequence_ ).size() - 1;

    for (; end >= 1; end--)
    {
        if ( ( *tmp_qual_sequence_ )[end] > QUAL_CUTOFF
            && ( *tmp_qual_sequence_ )[end - 1] > QUAL_CUTOFF )
        {
            ( *tmp_qual_sequence_ ) = ( *tmp_qual_sequence_ ).substr( 0, end + 1 );
            ( *tmp_genome_sequence_ ) = ( *tmp_genome_sequence_ ).substr( 0, end + 1 );
            
            break;
        }
    }

    if (end <= 1) 
    {
        end = 1;
        ( *tmp_qual_sequence_ ) = ( *tmp_qual_sequence_ ).substr( 0, end );
        ( *tmp_genome_sequence_ ) = ( *tmp_genome_sequence_ ).substr( 0, end );
    }

    size_t beg = 0;
    for ( ; beg <= ( *tmp_qual_sequence_ ).size() - 2; beg++ )
    {
        if ( ( *tmp_qual_sequence_ )[beg] > QUAL_CUTOFF
            && ( *tmp_qual_sequence_ )[beg + 1] > QUAL_CUTOFF) 
        {
            ( *tmp_qual_sequence_ ) = ( *tmp_qual_sequence_ ).substr(beg, (*tmp_qual_sequence_).size() - beg);
            ( *tmp_genome_sequence_ ) = ( *tmp_genome_sequence_ ).substr(beg, (*tmp_genome_sequence_).size() - beg);
            
            break;
        }
    }
}

HResult FastqReader::GetOneRead()
{
    if ( nullptr == fastq_input_ )
        return HResult::kFAIL;

    // iterate on every line, alloc some buffer before doing alignment
    string * line;

    char buffer[2000];

    //get 4 lines of a read
    for (int line_num = 0; line_num < 4; line_num++)
    {
        //no more data in file
        if ( nullptr == fgets( buffer, 1999, fastq_input_ ) )
        {
            return HResult::kFAIL;
        }

        //get the line
        line = new string( buffer );

        // skip empty lines, would not be one in common
        if ('\n' == ( *line )[0] || '\r' == ( *line )[0])
        {
            line_num--;
            continue;
        }

        // Remove blanks
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), '\n' ), ( *line ).end());
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), '\r' ), ( *line ).end());
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), ' ' ), ( *line ).end());

        // Fastq format, 0: read name, 1: read seq, 2: read name, 3: quals
        if ( ( ( line_num ) % 4 ) == 0 )
        {
            tmp_read_name_ = line;
        }

        else if ( ( ( line_num ) % 4 ) == 1 )
        {
            tmp_genome_sequence_ = line;
        }
        else if ( ( ( line_num ) % 4 ) == 3 )
        {
            tmp_qual_sequence_ = line;
        }

    }

    return HResult::kSUCCESS;
}

void FastqReader::ShapeAndClean()
{
    ToUpperCase();
    TrimByQuality();
}

void FastqReader::GenerateCurrentRead()
{
    // Beaware of memory leaking!!!
    current_read_ = new BasePairSequence();
    current_read_->Init();
    current_read_->set_original_basepair( tmp_genome_sequence_ );
    current_read_->set_qual( tmp_qual_sequence_ );
    current_read_->set_read_name( tmp_read_name_ );
    current_read_->set_original_basepair_size( tmp_genome_sequence_->length() );
}



