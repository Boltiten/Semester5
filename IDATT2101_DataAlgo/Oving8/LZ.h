#pragma once
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


class LZ
{
private:
    std::vector<char> bytesIn;
    char* compressed;

    std::vector<char> readFile(std::string path) {

        std::ifstream input(path, std::ios::binary);

        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        return bytes;
    }

    bool writeToFile(std::vector<char> compressed, std::string path) {

        std::ofstream FILE(path, std::ios::out | std::ofstream::binary);
        std::copy(compressed.begin(), compressed.end(), std::ostreambuf_iterator<char>(FILE));

        FILE.close();

        return true;
    }

    int find_match(std::vector<char> bytes_to_check, int start) {

        
        int max_back = start - 127;

        int back = 127;

        if (max_back < 0)
        {
            max_back = 0;
            back = start;
        }

        int index_return = 0;
        bool match_found = false;

        for (size_t i = max_back; i < back + max_back; i++)
        {

            match_found = true;
            int index = 0;

            for (size_t j = 0; j < bytes_to_check.size(); j++)
            {
                if (bytesIn[i + j] != bytes_to_check[index]) {
                    match_found = false;
                    break;
                }

                if (j == 0)
                {
                    index_return = i + j;
                }

                index++;

            }
            if (index == bytes_to_check.size())
            {
                break;
            }
        }

        if (match_found)
        {
            return index_return;
        }

        return -1;
    }

    std::vector<char> orginize_array(int buffer_length) {

        std::vector<char> tmp;

        for (size_t i = 0; i < buffer_length; i++)
        {
            tmp.push_back(compressed[i]);
        }

        return tmp;
    }

public:

    LZ(std::string path) {
        
        bytesIn = readFile(path);
        compressed = new char[bytesIn.size()];
    }

    std::vector<char> getbytes() {
        return bytesIn;
    }

 
    void compress() {

        int indexCompressedList = 0;

        int bytesDone = 0;

        int indexCompress = -1;

        for (size_t i = 0; i < bytesIn.size(); i++)
        {
            std::vector<char> currentBytes;

            bool compressFound = false;

            int compressLength = -1;

            int indexCompressMatch = 0;

            for (size_t j = i; j < bytesIn.size(); j++)
            {
                currentBytes.push_back(bytesIn[j]);

                if (currentBytes.size() >= 4)
                {
                    int compressPlace = find_match(currentBytes, i);

                    if (compressPlace >= 0)
                    {
                        compressFound = true;
                        indexCompress = i;
                        indexCompressMatch = compressPlace;
                        compressLength = currentBytes.size();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (compressFound)
            {
                int notCompressed = indexCompress - bytesDone;

                if (!(bytesIn.size() <= indexCompressedList))
                {
                    compressed[indexCompressedList] = (char) -notCompressed;
                    indexCompressedList++;
                }

                for (size_t x = bytesDone; x < indexCompress; x++)
                {
                    if (bytesIn.size() <= indexCompressedList || bytesIn.size() <= x) {
                        break;
                    }
                    compressed[indexCompressedList] = bytesIn[x];
                    indexCompressedList++;
                }

                if (!(bytesIn.size() <= indexCompressedList)) 
                {
                    compressed[indexCompressedList] = (char)(indexCompress - indexCompressMatch);
                    indexCompressedList++;
                    compressed[indexCompressedList] = (char)compressLength;
                    indexCompressedList++;
                }

                bytesDone = indexCompress + compressLength;
                i += compressLength;
            }

        }

        int not_compressed = bytesIn.size() - bytesDone;

        if (indexCompressedList < bytesIn.size())
        {
            compressed[indexCompressedList] = (char)-not_compressed;
            indexCompressedList++;
        }

        for (size_t j = bytesDone; j < bytesIn.size(); j++)
        {
            if (indexCompressedList >= bytesIn.size()) {
                break;
            }
            compressed[indexCompressedList] = bytesIn[j];
            indexCompressedList++;
        }

        writeToFile(orginize_array(indexCompressedList), "compressed.txt");
    }


};



