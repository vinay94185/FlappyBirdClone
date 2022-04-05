#ifndef DATALODER_H
#define DATALODER_H

#include <fstream>
#include <string>
#include <vector>
#include "Definations.h"


namespace vlc
{
    class DataLoder
    {
     	struct fileStruct
        {
            std::string path;
            unsigned long beg;
            unsigned long end;
        };
        protected:
            void LoadTable();
        public:
            DataLoder(const char *str);
            typedef std::vector<fileStruct> fs_vec;
            void GetBuffer(std::string name,char **buffer,size_t &size);
        private:
            fs_vec _file_struct;
            std::ifstream in;
    };
}
#endif // DATALODER_H
