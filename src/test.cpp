#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "huffman.h"

using namespace ptlmuh006;

TEST_CASE("Files correctly compressed", "[compression]"){
    HuffmanTree huff;

    SECTION("Frequency table corectly generated"){
        //GIVEN: A string of data
        std::string data = "aaabbbccc   dddddddddd\nccc";

        //WHEN: We count the frequency of the characters in the string of data
        std::unordered_map<char, int> freqTbl = huff.countFrequency(data);

        //THEN: We should get a correct frequency table with characters mapped to tallys
        REQUIRE( freqTbl.size() == 6 );
        REQUIRE( freqTbl['a'] == 3 );
        REQUIRE( freqTbl['b'] == 3 );
        REQUIRE( freqTbl['c'] == 6 );
        REQUIRE( freqTbl[' '] == 3 );
        REQUIRE( freqTbl['d'] == 10 );
        REQUIRE( freqTbl['\n'] == 1 );
    }

    SECTION("Tree correctly built"){
        //GIVEN: A string of data and it's corresponding frequency table
        std::string data = "aabbbcccc";
        std::unordered_map<char, int> freqTbl = {{'a', 2}, {'b', 3}, {'c', 4}};

        //WHEN: We try to build the huffmantree
        std::shared_ptr<HuffmanNode> root = huff.buildTree(data, freqTbl);

        //THEN: the tree should be built correctly
        REQUIRE( root->getFrequency() == 9 );

        std::shared_ptr<HuffmanNode> leftChild = root->getLeftChild();
        REQUIRE( leftChild != nullptr );
        REQUIRE( leftChild->getData() == 'c' );
        REQUIRE( leftChild->getFrequency() == 4 );

        std::shared_ptr<HuffmanNode> rightChild = root->getRightChild();
        REQUIRE( rightChild != nullptr );
        REQUIRE( rightChild->getData() == '\0' );
        REQUIRE( rightChild->getFrequency() == 5 );

        std::shared_ptr<HuffmanNode> rightLeftGrandChild = rightChild->getLeftChild();
        REQUIRE( rightLeftGrandChild != nullptr );
        REQUIRE( rightLeftGrandChild->getData() == 'a' );
        REQUIRE( rightLeftGrandChild->getFrequency() == 2 );

        std::shared_ptr<HuffmanNode> rightRightGrandChild = rightChild->getRightChild();
        REQUIRE( rightRightGrandChild != nullptr );
        REQUIRE( rightRightGrandChild->getData() == 'b' );
        REQUIRE( rightRightGrandChild->getFrequency() == 3 );
    }

    SECTION("Code table correctly generated"){
        //GIVEN: A properly constructed HuffmanTree
        std::shared_ptr<HuffmanNode> root(new HuffmanNode);
        root->setFrequency(9);

        std::shared_ptr<HuffmanNode> leftChild(new HuffmanNode);
        leftChild->setData('c');
        leftChild->setFrequency(4);
        root->setLeftChild(leftChild);

        std::shared_ptr<HuffmanNode> rightChild(new HuffmanNode);
        rightChild->setFrequency(5);
        root->setRightChild(rightChild);

        std::shared_ptr<HuffmanNode> rightLeftChild(new HuffmanNode);
        rightLeftChild->setData('a');
        rightLeftChild->setFrequency(2);
        rightChild->setLeftChild(rightLeftChild);

        std::shared_ptr<HuffmanNode> rightRightChild(new HuffmanNode);
        rightRightChild->setData('b');
        rightRightChild->setFrequency(3);
        rightChild->setRightChild(rightRightChild);

        //WHEN: We try to generate the corresponding Code Table
        std::unordered_map<char, std::string> codeTbl;
        huff.genCodeTbl(root, "", codeTbl);

        //THEN: The correct code table should be generated
        REQUIRE( codeTbl['a'] == "10" );
        REQUIRE( codeTbl['b'] == "11" );
        REQUIRE( codeTbl['c'] == "0" );
    }

    SECTION("Data correctly compressed"){
        //GIVEN: An input filename and output filename
        std::string inputFilename = "test";
        std::ofstream inputFile(inputFilename);
        inputFile << "aabbbbccccc\n";
        inputFile.close();

        std::string outputFilename = "compressed";

        //WHEN: We try to compress the inputfile to the outputfile
        huff.compress(inputFilename, outputFilename);

        //THEN: The correct compressed bitstring should be written to the output file
        std::ifstream compressedFile(outputFilename);
        std::string compressedString;
        REQUIRE( compressedFile.fail() == false );
        getline(compressedFile, compressedString);
        REQUIRE( compressedString == "1011011111111100000100");
        compressedFile.close();

        //THEN: The correct Code Table hould be written to the output file header
        std::ifstream headerFile(outputFilename + ".hdr");
        REQUIRE( headerFile.fail() == false );
        int numFields;
        headerFile >> numFields >> std::ws;
        REQUIRE( numFields == 4 );

        std::unordered_map<char, std::string> headerCodeTbl;
        while(!headerFile.eof()){
            std::string keyStr;
            std::string code;
            headerFile >> keyStr >> std::ws;
            headerFile >> code >> std::ws;
            headerFile >> std::ws;

            char key;
            if(keyStr == "/n"){
                key = '\n';
            }else if(keyStr == "/s"){
                key = ' ';
            }else{
                key = keyStr[0];
            }

            headerCodeTbl[key] = code;
        }
        REQUIRE( headerCodeTbl.size() == 4 );
        REQUIRE( headerCodeTbl['a'] == "101");
        REQUIRE( headerCodeTbl['b'] == "11");
        REQUIRE( headerCodeTbl['c'] == "0");
        REQUIRE( headerCodeTbl['\n'] == "100");
    }
}

TEST_CASE("Files correctly extracted", "[extraction]"){
    HuffmanTree huff;

    SECTION("Code table correctly read in from header file"){
        //GIVEN: The filename of some compressed input file to be extracted
        std::string

        //WHEN: We try to read in the code table stored in the header file

        //THEN: We should get the correct code table in the returned map
    }
}