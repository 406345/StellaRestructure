// Copyright (c) 2015 Yhgenomics. All rights reserved.
#ifndef STELLA_GEN_DATA_EXPORTER_H_
#define STELLA_GEN_DATA_EXPORTER_H_

#include <stdio.h>
#include <map>
#include <vector>

#include "Stella.h"

using namespace std;

// Export the basepair data and duplicate
class GeneDataExporter
{
public:

    GeneDataExporter();
    ~GeneDataExporter();

    void ExportBasePairData(const char* file_name, void* data, size_t data_size);
    void ExportDuplicate(const char* file_name, void* data, size_t data_size);

private:
    
    std::map<int, vector<size_t> > code_pos_map_;
};

#endif //STELLA_GEN_DATA_EXPORTER_H_