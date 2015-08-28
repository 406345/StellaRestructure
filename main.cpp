#include "stdio.h"
#define TEST_BY_BIGCAT
#ifdef TEST_BY_BIGCAT

#include "FastqReader.h"
#include "AlignerResultFileExporter.h"
#include "Stella.h"

#endif

int main(int argc, char* argv[]) 
{
#ifdef TEST_BY_BIGCAT
    FastqReader test_reader;
    test_reader.Init();
    test_reader.SetData("F:\\STELLADATA\\handmake.fastq");
    BasePairSequence * testbps = test_reader.Next();
    BasePairCodeSample testcode;
    testbps->ReadCode(&testcode);

    //AlignerResultFileExporter test_exporter;
    //AlignerResult test_aligner_result;
    
#endif


}