#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>
#include <string>

namespace ptlmuh006{

    class HuffmanNode{
        private:
            char data;
            int frequency;
            std::shared_ptr<HuffmanNode> leftChild;
            std::shared_ptr<HuffmanNode> rightChild;

        public:
            //default constructor
            HuffmanNode(char dat = '\0', int freq = 0): data(dat), frequency(freq), leftChild(nullptr), rightChild(nullptr){};
            HuffmanNode(const HuffmanNode& other);          //copy constructor
            HuffmanNode(HuffmanNode&& other);               //move constructor
            ~HuffmanNode();                                 //destructor
            HuffmanNode& operator= (const HuffmanNode& rhs);//copy assignment
            HuffmanNode& operator= (HuffmanNode&& rhs);     //move assignment

            char getData();
            int getFrequency();
            void setData(char newData);
            void setFrequency(int frequency);
            void setLeftChild(std::shared_ptr<HuffmanNode> newLeft);
            void setRightChild(std::shared_ptr<HuffmanNode> newRight);
            std::shared_ptr<HuffmanNode> getLeftChild();
            std::shared_ptr<HuffmanNode> getRightChild();
            static bool compareNodes(std::shared_ptr<HuffmanNode> one, std::shared_ptr<HuffmanNode> other);
    };

    class HuffmanTree{
        private:
            std::shared_ptr<HuffmanNode> root;

        public:
            HuffmanTree(): root(nullptr){};                 //default constructor
            HuffmanTree(const HuffmanTree& other);          //copy constructor
            HuffmanTree(HuffmanTree&& other);               //move constructor
            ~HuffmanTree();                                 //destructor
            HuffmanTree& operator= (const HuffmanTree& rhs);//copy assignment
            HuffmanTree& operator= (HuffmanTree&& rhs);     //move assignment

        public:
            void compress(std::string data, std::string outfilename);
            void extract(std::string inputfilename);

        private:
            void build(std::string data);
            void genCodeTbl(std::shared_ptr<HuffmanNode> current, std::string code);
            void addToTree(char key, std::string code);
    };
}

#endif