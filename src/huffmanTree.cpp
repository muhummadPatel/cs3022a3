#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#include "huffman.h"
#include "reader.h"

namespace ptlmuh006{

    using namespace std;

    //TODO: move to header file?
    unordered_map<char, std::string> codeTbl;

    HuffmanTree::HuffmanTree(const HuffmanTree& other){
        //copy constructor
        root = other.root;
    }

    HuffmanTree::HuffmanTree(HuffmanTree&& other){
        //move constructor
        root = other.root;

        other.root = nullptr;
    }

    HuffmanTree::~HuffmanTree(){
        //destructor
        //TODO: anything to put here really?
    }

    HuffmanTree& HuffmanTree::operator= (const HuffmanTree& rhs){
        //copy assignment
        root = rhs.root;

        return *this;
    }

    HuffmanTree& HuffmanTree::operator= (HuffmanTree&& rhs){
        //move assignment
        root = rhs.root;

        rhs.root = nullptr;

        return *this;
    }

    //TODO: Move this to somewhere decent
    bool compare(shared_ptr<HuffmanNode> one, shared_ptr<HuffmanNode> other){
            return (one->getFrequency() > other->getFrequency());
    }

    void HuffmanTree::build(std::string data){
        //TODO: split these up into seperate private methods?
        //counting occurrences
        unordered_map<char, int> freqTbl;
        for(int i = 0; i < data.length(); i++){
            freqTbl[data[i]]++;
        }

//        for(auto it = freqTbl.begin(); it != freqTbl.end(); ++it){
//            cout << it->first << " occurs " << it->second << " times" << endl;
//        }

        //create the priority queue
        typedef bool(*fptr)(shared_ptr<HuffmanNode>, shared_ptr<HuffmanNode>);

        priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, fptr> q(compare);
        for(auto it = freqTbl.begin(); it != freqTbl.end(); ++it){
            //TODO: fix this shit
            shared_ptr<HuffmanNode> temp(new HuffmanNode(it->first, it->second));
//            q.push(HuffmanNode(it->first, it->second));
            q.push(temp);
        }

//        while(!q.empty()){
//            HuffmanNode i = q.top();
//            cout << "q top " << i.getData() << " freq " << i.getFrequency() << endl;
//            q.pop();
//        }

        while(q.size() > 1){
            shared_ptr<HuffmanNode> n1 = q.top(); q.pop();
            shared_ptr<HuffmanNode> n2 = q.top(); q.pop();

            if(n1->getFrequency() < n2->getFrequency()){
                //n1 should be the left child
                shared_ptr<HuffmanNode> temp(new HuffmanNode);
                temp->setLeftChild(n1);
                temp->setRightChild(n2);
                temp->setFrequency(n2->getFrequency() + n1->getFrequency());

                q.push(temp);
            }else{
                //n2 should be the left child
                shared_ptr<HuffmanNode> temp(new HuffmanNode);
                temp->setLeftChild(n2);
                temp->setRightChild(n1);
                temp->setFrequency(n2->getFrequency() + n1->getFrequency());

                q.push(temp);
            }
        }

        cout << q.size() << " and top is " << q.top()->getFrequency() << endl;
        root = q.top(); q.pop();

        //build code table
        genCodeTbl(root, "");
        cout << "size is " << codeTbl.size() << endl;
    }


    void HuffmanTree::genCodeTbl(shared_ptr<HuffmanNode> current, std::string code){
        if(current != nullptr){
            genCodeTbl(current->getLeftChild(), code + "0");

            if(current->getData() != '\0'){
                //leaf node, so put code in the table
                cout << current->getData() << " code: " << code << endl;
                codeTbl[current->getData()] = code;
            }

            genCodeTbl(current->getRightChild(), code + "1");
        }
    }


    void HuffmanTree::compress(std::string data, std::string outFilename){
        ostringstream oss;
        for(int i = 0; i < data.length(); i++){
            oss << codeTbl[data[i]];
        }

        //writing compressed data to output file
        string output = oss.str();
        cout << "outputted stuff: " << output << endl;
        ofstream outfile(outFilename);
        outfile << output;
        outfile.close();

        //writing code table to header file
        ofstream hdrfile(outFilename + ".hdr");
        hdrfile << codeTbl.size() << endl;
        for(auto it = codeTbl.begin(); it != codeTbl.end(); ++it){
            ostringstream ss;
            ss << it->first;
            string ch = ss.str();

            if(ch == " "){
                ch = "/s";
            }else if(ch == "\n"){
                ch = "/n";
            }

            hdrfile << ch << " " << it->second << endl;
        }
        hdrfile.close();
    }

    void HuffmanTree::extract(std::string inputfilename){
        unordered_map<char, std::string> newCodeTbl;

        ifstream hdrFile(inputfilename + ".hdr");

        int numFields;
        hdrFile >> numFields >> ws;
        cout << "numFields " << numFields << endl;

        //TODO: check this matches with expected fields
        //read in code table stored in header file
        std::string data;
        while(getline(hdrFile, data)){
            //cout << "_" << data << "_" << endl;
            istringstream iss(data);
            char key;
            string temp;
            iss >> temp >> ws;
            if(temp == "/s"){
                key = ' ';
            }else if(temp == "/n"){
                key = '\n';
            }else{
                key = temp[0];
            }
            string code;
            iss >> code >> ws;
            cout << "key " << key << " code " << code << endl;

            newCodeTbl[key] = code;
        }

        codeTbl = std::move(newCodeTbl);

        //build huffman tree represented by the new code table
        root.reset(new HuffmanNode);
        for(auto it = codeTbl.begin(); it != codeTbl.end(); ++it){
            cout << "aight" << endl;
            addToTree(it->first, it->second);
        }

        //decode input by decoding one letter at a time
        ifstream compressedFile(inputfilename);
        string encodedData;
        getline(compressedFile, encodedData);
        ostringstream oss;
        int index = 0;
        shared_ptr<HuffmanNode> curr = root;
        cout << root->getLeftChild() << endl;

        while(index < encodedData.length()){
            if(curr->getData() != '\0'){
                oss << curr->getData();
            }

            if((int)encodedData[index] == 0){
                curr = curr->getLeftChild();
            }else{
                curr = curr->getLeftChild();
            }
            index++;
        }
    }

    void HuffmanTree::addToTree(char key, string code){
        shared_ptr<HuffmanNode> currNode;
        currNode = root;
        for(int i = 0; i < code.length(); i++){


            if(code[i] == '0'){
//                cout << "yo" << endl;
                if(currNode->getLeftChild() == nullptr){
                    shared_ptr<HuffmanNode> emptyNode(new HuffmanNode);
                    currNode->setLeftChild(emptyNode);
//                    cout << "here " << currNode->getLeftChild() << endl;
                }
                currNode = currNode->getLeftChild();
            }else{
//                cout << "LO" << endl;
                if(currNode->getRightChild() == nullptr){
                    shared_ptr<HuffmanNode> emptyNode(new HuffmanNode);
                    currNode->setRightChild(emptyNode);
                }
                currNode = currNode->getRightChild();
            }
        }
        currNode->setData(key);
    }
}