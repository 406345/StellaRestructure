#include "stdio.h"
#define TEST_BY_BIGCAT
#ifdef TEST_BY_BIGCAT

#include "FastqReader.h"

#endif

int main(int argc, char* argv[]) 
{
#ifdef TEST_BY_BIGCAT
	FastqReader test_reader;
	test_reader.Init();
	test_reader.SetData("F:\\STELLADATA\\test.fastq");
	test_reader.Next();
#endif


}