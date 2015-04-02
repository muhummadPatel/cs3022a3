#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>
#include <unordered_map>
#include <string>

namespace ptlmuh006{

    //TODO: add in parameter names
    class HuffmanNode{
        private:
            char data;
            int frequency;
            std::shared_ptr<HuffmanNode> leftChild;
            std::shared_ptr<HuffmanNode> rightChild;

        public:
            //default constructor
            HuffmanNode(char dat = '\0', int freq = 0): data(dat), frequency(freq), leftChild(nullptr), rightChild(nullptr){};
            //copy constructor
            HuffmanNode(const HuffmanNode& other);
            //move constructor
            HuffmanNode(HuffmanNode&& other);
            //destructor
            ~HuffmanNode();
            //copy assignment
            HuffmanNode& operator= (const HuffmanNode& rhs);
            //move assignment
            HuffmanNode& operator= (HuffmanNode&& rhs);

            char getData();
            int getFrequency();
            void setData(char);
            void setFrequency(int);
            void setLeftChild(std::shared_ptr<HuffmanNode>);
            void setRightChild(std::shared_ptr<HuffmanNode>);
            std::shared_ptr<HuffmanNode> getLeftChild();
            std::shared_ptr<HuffmanNode> getRightChild();
            //static bool compare(HuffmanNode, HuffmanNode);
    };

    class HuffmanTree{
        private:
            std::shared_ptr<HuffmanNode> root;
//            std::unordered_map<char, std::string> codeTbl;

        public:
            //default constructor
            HuffmanTree(): root(nullptr){};
            //copy constructor
            HuffmanTree(const HuffmanTree& other);
            //move constructor
            HuffmanTree(HuffmanTree&& other);
            //destructor
            ~HuffmanTree();
            //copy assignment
            HuffmanTree& operator= (const HuffmanTree& rhs);
            //move assignment
            HuffmanTree& operator= (HuffmanTree&& rhs);

            //TODO: some of these should be private
            void build(std::string);
            void genCodeTbl(std::shared_ptr<HuffmanNode>, std::string);
            void compress(std::string, std::string);
            void extract(std::string);
            void addToTree(char, std::string);
    };

}

#endif