#include "stdio.h"

#include "Stella.h"
#include "GeneDataExporter.h"
#include "SharedGeneData.h"
#include "FastqReader.h"
#include "BasePairSequence.h"
#include "BasePairSequenceAligner.h"

//#define YSB_DEBUG
//#define TEST_BY_BIGCAT

#ifdef TEST_BY_BIGCAT

#include "FastqReader.h"
#include "AlignerResultFileExporter.h"
#include "Stella.h"

#endif 

#ifdef YSB_DEBUG

#include <string>
#include "BasePairSequenceDifferencesDetector.h"

#endif

void Run(char* genome_file, char* base_pair, char* duplicate_file, char* input_file);

int main(int argc, char* argv[]) 
{
#ifdef YSB_DEBUG
    printf("BasePairIndex size :%d\r\n", sizeof(BasePairIndex));
    printf("unsigned in size :%d\r\n", sizeof(unsigned int));
    printf("size_t size :%d\r\n", sizeof(size_t));

    string s1 = "*ATCGT";
    string s2 = "*AGT";
    string sa, sb, sm;
    BasePairSequenceDifferencesDetector detector;
    detector.clear();
    auto ret = detector.NeedlemanWunsch(s1, s2, sa, sb, sm, -3, 0);

#endif
    if (5 == argc && argv[1][0] == 'e')
    {
        // Argv[1] == e
        // Argv[2] == hg19
        // Argv[3] == basepair 
        // Argv[4] == duplicate
        GeneDataExporter exporter;
        FILE* file_hg19;

        fopen_s(&file_hg19, argv[2], "r");
        fseek(file_hg19, 0, SEEK_END);
        auto file_length = _ftelli64(file_hg19);
        char* buffer = new char[file_length] {};
        fseek(file_hg19, 0, SEEK_SET);
        fread_s(buffer, file_length, 1, file_length, file_hg19);
        fclose(file_hg19);

        exporter.ExportBasePairData(argv[3], buffer, file_length);
        exporter.ExportDuplicate(argv[4]);

        return 0;
    }
    else if(5 == argc)
    {
        // Argv[1] == hg19
        // Argv[2] == basepair
        // Argv[3] == duplicate 
        // Argv[4] == input files
        Run(argv[1], argv[2], argv[3], argv[4]); 
    }

    printf("argv errors...\r\n");

#ifdef TEST_BY_BIGCAT
    FastqReader test_reader;
    test_reader.Init();
    test_reader.SetData("F:\\STELLADATA\\handmake.fastq");
    BasePairSequence * testbps = test_reader.Next();
    BasePairCodeSample testcode;
    for (int i = 0; i < MAX_BP_LEN;i++)
    {
    testbps->ReadCode(&testcode);
    }
    system("pause");
    //AlignerResultFileExporter test_exporter;
    //AlignerResult test_aligner_result;
    
#endif

    return 0;
}

void Run(char* genome_file, char* base_pair, char* duplicate_file, char* input_file) 
{
    
    // Load static data 
    SharedGeneData::instance()->LoadFromFile(genome_file, base_pair, duplicate_file);

    // Init fastq reader
    FastqReader reader;
    reader.Init();
    reader.SetData(input_file);

    BasePairSequence* seq = nullptr;

    do
    {
        SAFE_DELETE(seq);

        seq = reader.Next();

        if (nullptr == seq)break;
        
        BasePairSequenceAligner aligner;
        aligner.SetData(seq, SharedGeneData::instance());

        if (kFAIL == aligner.Search()) continue;

        if (kFAIL == aligner.Filter()) continue;

        if (kFAIL == aligner.Diff()) continue;

        aligner.QueryResult();
    } 
    while (1);

    scanf_s("");
}