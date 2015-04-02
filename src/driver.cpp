#include <iostream>

#include "huffman.h"

int main(int argc, char* argv[]) {
    using namespace ptlmuh006;

    if(argc != 4){
        std::cout << "Incorrect usage." << std::endl;
        std::cout << "Please use huffencode as follows:" << std::endl;
        std::cout << "huffencode <option> <inputFilename> <outputFilename>" << std::endl;
        std::cout << "\t___options:___" << std::endl;
        std::cout << "\t -c compress data from inputFilename to outputFilename" << std::endl;
        std::cout << "\t -x extract compressed data from inputFilename to outputFilename" << std::endl;

    }else{
        HuffmanTree* huff = new HuffmanTree;

        std::string option = argv[1];
        if(option == "-c"){
            huff->compress(argv[2], argv[3]);
            std::cout << "Compressed " << argv[2] << " into " << argv[3] << "." << std::endl;

        }else if(option == "-x"){
            huff->extract(argv[2], argv[3]);
            std::cout << "Extracted from " << argv[2] << " into " << argv[3] << "." << std::endl;
        }

        delete huff;
    }
    return 0;
}