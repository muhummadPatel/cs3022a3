#include <iostream>

#include "reader.h"
#include "huffman.h"

int main(int argc, const char* argv[]) {
    using namespace ptlmuh006;

    //std::string fil = readFile("test.txt");
    HuffmanTree ht;
    //ht.build(fil);
    ht.compress("test.txt", "testout");
    ht.extract("testout");

    return 0;
}