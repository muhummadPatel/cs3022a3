#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>
#include <unordered_map>

namespace ptlmuh006{

    class HuffmanNode{
        private:
            char data;
            int frequency;
            std::shared_ptr<HuffmanNode> leftChild;
            std::shared_ptr<HuffmanNode> rightChild;

        public:
            HuffmanNode(char dat = '\0', int freq = 0): data(dat), frequency(freq), leftChild(nullptr), rightChild(nullptr){};
            //TODO: oher RAII methods here

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
            HuffmanTree(): root(nullptr){};
            //TODO: other RAII methods here

            void build(std::string data);
            void genCodeTbl(std::shared_ptr<HuffmanNode>, std::string);
    };

}

#endif