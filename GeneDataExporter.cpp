#include "GeneDataExporter.h"

#include "stdio.h"

GeneDataExporter::GeneDataExporter()
{
}

GeneDataExporter::~GeneDataExporter()
{
}

void GeneDataExporter::ExportBasePairData(const char * file_name, void * data, size_t data_size)
{
    char* pdata = static_cast<char*>(data);
    char* pcur = pdata;
    int code_len = 0;
    unsigned int code = 0;
    size_t pos = 0;

    for (size_t i = 0; i < data_size; i++)
    {
        if (i % 500000 == 0) 
        {
            printf("Processed %f \r\n",((double)i/ (double)data_size)*100.0f);
        }

        if (pcur[i] == '>')
        {
            do { i++; pos++; } while (pcur[i] != '\n' || pcur[i] == '\r');
            continue;
        }
        else if (pcur[i] == '\n' || pcur[i] == '\r')
        {
            continue;
        }
        else
        {
            char value = pcur[i];
            code += (BitCodes[value - 'A'] << (code_len * CODE_LEN));

            if (code_len == MAX_BP_LEN)
            {
                
                auto map_value = code_pos_map_.find(code);
                if (map_value == code_pos_map_.end()) {
                    code_pos_map_.insert(make_pair(code, vector<size_t>()));
                }

                code_pos_map_[code].push_back(i);
                code = 0;

                code_len = 0;
            }
            else
            {
                code_len++;
            }
        }
    }

    FILE* pfile;
    auto error = fopen_s(&pfile, file_name, "w+");

    if (error) {
#ifdef DEBUG
        printf("create basepair file fail...\r\n");
#endif
        return;
    }

    BasePairIndex index;
    size_t offset = 0;
    size_t count = static_cast<size_t>(code_pos_map_.size());

    fwrite(&count, sizeof(size_t), 1, pfile);

    for (std::map<int, vector<size_t>>::iterator iter = code_pos_map_.begin(); iter != code_pos_map_.end(); iter++)
    {
        auto kv = *iter;

        index.code = kv.first;
        index.count = static_cast<size_t>(kv.second.size());
        index.offset = offset;
        offset += kv.second.size();

        fwrite(&index, sizeof(BasePairIndex), 1, pfile);
    }

    fclose(pfile);
}
    
void GeneDataExporter::ExportDuplicate(const char * file_name)
{
    FILE* pfile;
    auto error = fopen_s(&pfile,file_name, "w+");
    
    if (error) {
#ifdef DEBUG
        printf("create duplicate file fail...\r\n");
#endif
        return;
    }
    
    size_t count = 0;
    fwrite(&count, sizeof(size_t), 1, pfile);
    
    for (std::map<int, vector<size_t>>::iterator iter = code_pos_map_.begin(); iter != code_pos_map_.end(); iter++)
    {
        auto kv = *iter;
        for (auto e = kv.second.begin(); e != kv.second.end(); e++)
        {
            fwrite(&(*e), sizeof(size_t), 1, pfile);
        }
    
        count += kv.second.size();
    }
    
    fseek(pfile, 0, SEEK_SET);
    fwrite(&count, sizeof(size_t), 1, pfile);
    
    fclose(pfile);
}
