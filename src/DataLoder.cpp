#include "DataLoder.h"

namespace vlc
{

    DataLoder::DataLoder(const char *str):in(str,std::ios::binary) { }

    void DataLoder::LoadTable()
    {
        unsigned long int table_index = 0; // contains the index of file
        in.seekg(0, std::ios::end);

        /*
        ** first unsigned long int sized bytes containts the
        ** index of the position where the table starts
        ** that will contain further informatio on the
        ** data within the file.
        */
        in.seekg(0, std::ios::beg);
        in.read((char *)&table_index, sizeof(unsigned long int));

        // move file pointer to the starting point of the index
        in.seekg(table_index);

        std::string str; // read one line at a time into this
        std::string::size_type path, beg, end; // to store the position of data
        fileStruct fileData; // temp data struct to hold the data
        /*
        ** read the table from the file and store tha read
        ** data into the vector called (_file_struct)
        ** for later usage
        */
        while(!in.eof())
        {
            getline(in,str); // read a line from file
            // find the position of the data in the string
            // so that we can extract it later.
            path = str.find_first_of("Path : \\");
            beg = str.find_last_of("Beg");
            end = str.find_last_of("End");
            // if path is not found in the struct  leave the item
            if (path != std::string::npos)
            {
                // store data into a temp data structure for pushing into the vector
                fileData.path = str.substr(path + 8, (beg - (path + 8)) - 3); //get file path from string
                fileData.beg = stoul(str.substr(beg + 4, (end - beg) - 6)); // get begining of file as unsigned long int
                fileData.end = stoul(str.substr(end + 4, str.size() - (end + 3))); // get end of file as unsigned long int

                this->_file_struct.push_back(fileData);
            }
        }
        in.seekg(0, std::ios::beg);
        in.clear();
    }

    void DataLoder::GetBuffer(std::string name,char **buffer,size_t &size)
    {
        std::string::size_type filename_pos = std::string::npos;
        size_t  filesize = 0;
        std::streampos read_pointer; // will hold the starting point of the file that we are going to extract
        std::string::size_type root_pos = name.find_first_not_of(ROOT_DIR);
        name = name.substr(root_pos+1, name.size() - root_pos);
        for(auto it = this->_file_struct.cbegin();
            it != this->_file_struct.cend();++it)
        {
            if(it->path == name)
            {
                filename_pos = it->path.find_last_of("\\");
                filesize = (it->end - it->beg);
                size = filesize;
                read_pointer = it->beg;
                in.seekg(read_pointer,std::ios::beg); // set file pointer to starting point of the file and read the filzesize bytes
                *buffer = new char[filesize]; // allocate a buffer to transfer file
                in.read(*buffer, filesize);
                break;
            }
        }
        // reset the object so we can further operate on it
        // because it was set to off after this function
        in.seekg(0, std::ios::beg);
        in.clear();
    }
}
