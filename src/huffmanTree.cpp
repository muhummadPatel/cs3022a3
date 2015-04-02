/*
 * HuffmanTree class implementation. This class models a HuffmanTree which consists of one or more HuffmanNodes. The
 * tree allows for the compression and extraction of data. The 'compressed' data is actually written out as a string
 * which means that it may not actually be compresses. This is just a demonstration of the concept.
 *
 * Muhummad Patel
 * 07-Apr-2015
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    //helper method used to read in the specified file as a single string
    string readFile(string filename){
        ostringstream outstr;

        ifstream infile(filename);
        std::string line;
        while(std::getline(infile, line)){
            outstr << line << "\n";
        }

        return outstr.str();
    }

    //copy constructor
    HuffmanTree::HuffmanTree(const HuffmanTree& other){
        root = other.root;
    }

    //move constructor
    HuffmanTree::HuffmanTree(HuffmanTree&& other){
        root = other.root;

        other.root = nullptr;
    }

    //destructor
    HuffmanTree::~HuffmanTree(){
    }

    //copy assignment
    HuffmanTree& HuffmanTree::operator= (const HuffmanTree& rhs){
        root = rhs.root;

        return *this;
    }

    //move assignment
    HuffmanTree& HuffmanTree::operator= (HuffmanTree&& rhs){
        root = rhs.root;
        rhs.root = nullptr;

        return *this;
    }

    //==================COMPRESSION==================

    //compresses the data stored in infilename and puts the compressed data in outfilename and outfilename.hdr. The data
    //is compressed by first building a huffman tree corresponding to the given data, and then compressing it, using
    //the generated codetable.
    void HuffmanTree::compress(std::string inFilename, std::string outFilename){
        //read in file to be compressed
        string data = readFile(inFilename);

        //counting occurrences of characters
        unordered_map<char, int> freqTbl = countFrequency(data);

        //build the corresponding huffman tree
        root = buildTree(data, freqTbl);

        //build code table from the tree
        unordered_map<char, string> codeTbl;
        genCodeTbl(root, "", codeTbl);

        //build up the compressed version using the code table
        ostringstream compressedData;
        for(int i = 0; i < data.length(); i++){
            compressedData << codeTbl[data[i]];
        }

        //writing compressed data to output file
        ofstream outfile(outFilename);
        outfile << compressedData.str();
        outfile.close();

        //writing code table to header file (to allow for extraction later on)
        ofstream hdrfile(outFilename + ".hdr");
        hdrfile << codeTbl.size() << endl; //number of fields to be read in
        for(auto it = codeTbl.begin(); it != codeTbl.end(); ++it){
            ostringstream ss;
            ss << it->first;
            string ch = ss.str();

            //use special character sequences for spaces and newlines in the header file
            if(ch == " "){
                ch = "/s"; //'escaped' space
            }else if(ch == "\n"){
                ch = "/n"; //'escaped' newline
            }

            //write the character and the corresponding code to the header file
            hdrfile << ch << " " << it->second << endl;
        }
        hdrfile.close();
    }

    //returns an unordered_map with the frequency table corresponding to the given data.
     unordered_map<char, int> HuffmanTree::countFrequency(string data){
        unordered_map<char, int> freqTbl;
        for(int i = 0; i < data.length(); i++){
            freqTbl[data[i]]++;
        }

        return freqTbl;
    }

    //builds a huffman tree that corresponds to the data passed in as the argument. The tree built, is then stored in
    //the object (a reference to the tree root is stored in the root member of this object).
    std::shared_ptr<HuffmanNode> HuffmanTree::buildTree(string data, unordered_map<char, int> freqTbl){
        //create the priority queue
        typedef bool(*fptr)(shared_ptr<HuffmanNode>, shared_ptr<HuffmanNode>);
        priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, fptr> q(HuffmanNode::compareNodes);
        for(auto it = freqTbl.begin(); it != freqTbl.end(); ++it){
            char key = it->first;
            int frequency = it->second;
            shared_ptr<HuffmanNode> temp(new HuffmanNode(key, frequency));

            q.push(temp);
        }

        //build the tree from the priority queue until there is only the root left
        while(q.size() > 1){
            shared_ptr<HuffmanNode> min1 = q.top(); q.pop();
            shared_ptr<HuffmanNode> min2 = q.top(); q.pop();

            if(min1->getFrequency() < min2->getFrequency()){
                //min1 should be the left child
                shared_ptr<HuffmanNode> temp(new HuffmanNode);
                temp->setLeftChild(min1);
                temp->setRightChild(min2);
                temp->setFrequency(min2->getFrequency() + min1->getFrequency());

                q.push(temp);
            }else{
                //min2 should be the left child
                shared_ptr<HuffmanNode> temp(new HuffmanNode);
                temp->setLeftChild(min2);
                temp->setRightChild(min1);
                temp->setFrequency(min2->getFrequency() + min1->getFrequency());

                q.push(temp);
            }
        }
        //return the root of the tree to be stored in the root variable of this object
        return q.top();
    }

    //recursively walks through the tree building up the code as it branches and when it hits a leaf, it adds the data
    //at that leaf and the code for that character to the codeTable.
     void HuffmanTree::genCodeTbl(shared_ptr<HuffmanNode> current, std::string code, std::unordered_map<char, std::string>& codeTbl){
        if(current != nullptr){
            genCodeTbl(current->getLeftChild(), code + "0", codeTbl);

            if(current->getData() != '\0'){
                //leaf node, so put code in the table
                codeTbl[current->getData()] = code;
            }

            genCodeTbl(current->getRightChild(), code + "1", codeTbl);
        }
    }



    //==================EXTRACTION==================

    //extracts original data from the compressed version using the hdr file. It generates a huffman tree from the code
    //table stored in the header file and then uses the tree to decompress the data. The decompressed data is stored in
    //extracted_inputfilename.
    void HuffmanTree::extract(string inputfilename, string outputfilename){
        //read in code table stored in header file
        unordered_map<char, string> codeTbl = readInCodeTable(inputfilename);

        //build huffman tree represented by the new code table
        root.reset(new HuffmanNode); //resetting the tree
        for(auto it = codeTbl.begin(); it != codeTbl.end(); ++it){
            char key = it->first;
            string code = it->second;
            addToTree(key, code);
        }

        //read in file to be extracted
        ifstream compressedFile(inputfilename);
        string encodedData;
        getline(compressedFile, encodedData);

        //loop through the encoded string and decode as we go along
        ostringstream extractedData;
        int index = 0;
        shared_ptr<HuffmanNode> curr = root;
        while(index < encodedData.length()){
            //follow branches

            if(curr->getData() != '\0'){
                //when we hit a leaf, add this data to the extractedData stream
                extractedData << curr->getData();
                curr = root; //start at the root again
            }

            //follow down to the next branch specified by the compressed string
            if(encodedData[index] == '0'){
                curr = curr->getLeftChild(); //branch left
            }else{
                curr = curr->getRightChild(); //branch right
            }

            index++;
        }

        //write extracted data to output file.
        ofstream extracted(outputfilename);
        extracted << extractedData.str();
    }

    unordered_map<char, string> HuffmanTree::readInCodeTable(string inputfilename){
        unordered_map<char, string> codeTbl;

        fstream hdrFile(inputfilename + ".hdr");
        int numFields;
        hdrFile >> numFields >> ws;

        int count = 0;
        string data;
        while(getline(hdrFile, data) && count < numFields){

            //read in key as a string to account for multi characer sequences for newlines and spaces
            istringstream iss(data);
            string temp;
            iss >> temp >> ws;

            char key;
            if(temp == "/s"){
                key = ' '; //turn escaped space into actual space in the codeTable
            }else if(temp == "/n"){
                key = '\n'; //store escaped newline as an actual newline character in the codeTable
            }else{
                key = temp[0]; //store the actual character, whatever it is
            }

            //get the code corresponding to this character
            string code;
            iss >> code >> ws;

            codeTbl[key] = code;
            count++;
        }

        return codeTbl;
    }

    //helper method used when building huffman tree from a code table for extraction purposes. This method will add the
    //given key into the tree at the location specified by the code and will build the tree as it goes along if
    //neccessary.
    void HuffmanTree::addToTree(char key, string code){
        shared_ptr<HuffmanNode> currNode;
        currNode = root;

        //follow branches specified by code all the way down the tree building as we go if neccessary
        for(int i = 0; i < code.length(); i++){
            if(code[i] == '0'){
                if(currNode->getLeftChild() == nullptr){
                    shared_ptr<HuffmanNode> emptyNode(new HuffmanNode);
                    currNode->setLeftChild(emptyNode);
                }
                currNode = currNode->getLeftChild();
            }else{
                if(currNode->getRightChild() == nullptr){
                    shared_ptr<HuffmanNode> emptyNode(new HuffmanNode);
                    currNode->setRightChild(emptyNode);
                }
                currNode = currNode->getRightChild();
            }
        }

        //put the corresponding data at the appropriate location
        currNode->setData(key);
    }
}