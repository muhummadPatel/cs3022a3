/*
 * Header file containing the declarations for the HuffmanNode and HuffmanTree classes.
 *
 * Muhummad Patel
 * 07-Apr-2015
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>
#include <string>
#include <unordered_map>

namespace ptlmuh006{

    //A class modelling a single node in a Huffman Tree
    class HuffmanNode{
        //private class members
        private:
            char data; //the character this node refers to (empty for internal nodes)
            int frequency; //number of time the character appeared in data
            std::shared_ptr<HuffmanNode> leftChild;
            std::shared_ptr<HuffmanNode> rightChild;

        public:
            //RAII methods so that class behaves consistently
            HuffmanNode(char dat = '\0', int freq = 0): data(dat), frequency(freq), leftChild(nullptr), rightChild(nullptr){};
            HuffmanNode(const HuffmanNode& other);          //copy constructor
            HuffmanNode(HuffmanNode&& other);               //move constructor
            ~HuffmanNode();                                 //destructor
            HuffmanNode& operator= (const HuffmanNode& rhs);//copy assignment
            HuffmanNode& operator= (HuffmanNode&& rhs);     //move assignment

            //accessors and mutators
            char getData();
            int getFrequency();
            void setData(char newData);
            void setFrequency(int frequency);
            void setLeftChild(std::shared_ptr<HuffmanNode> newLeft);
            void setRightChild(std::shared_ptr<HuffmanNode> newRight);
            std::shared_ptr<HuffmanNode> getLeftChild();
            std::shared_ptr<HuffmanNode> getRightChild();

            //method to compare two nodes. Used to order a priorityQueue
            static bool compareNodes(std::shared_ptr<HuffmanNode> one, std::shared_ptr<HuffmanNode> other);
    };

    class HuffmanTree{
        //private class members
        private:
            std::shared_ptr<HuffmanNode> root;

        //RAII methods so that the class behaves consistently
        public:
            HuffmanTree(): root(nullptr){};                 //default constructor
            HuffmanTree(const HuffmanTree& other);          //copy constructor
            HuffmanTree(HuffmanTree&& other);               //move constructor
            ~HuffmanTree();                                 //destructor
            HuffmanTree& operator= (const HuffmanTree& rhs);//copy assignment
            HuffmanTree& operator= (HuffmanTree&& rhs);     //move assignment

        //public methods to allow compression and extraction of data
        public:
            void compress(std::string data, std::string outfilename);
            void extract(std::string inputfilename, std::string outputfilename);

        //internal/private methods used to compress or extract the data
        private:
            std::unordered_map<char, int> countFrequency(std::string data);
            std::unordered_map<char, std::string> genCodeTbl(std::shared_ptr<HuffmanNode> current, std::string code); //generates codeTable from tree
            void buildTree(std::string data, std::unordered_map<char, int> freqTbl); //builds h-tree from codeTable
            std::unordered_map<char, std::string> readInCodeTable(std::string inputfilename);
            void addToTree(char key, std::string code); //used to help build tree from codeTable
    };
}

#endif