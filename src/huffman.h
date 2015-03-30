#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <memory>

namespace ptlmuh006{

    class HuffmanNode{
        private:
            char data;
            int frequency;
            std::shared_ptr<HuffmanNode> leftChild;
            std::shared_ptr<HuffmanNode> rightChild;

        public:
            HuffmanNode(char dat = '\0', int freq = 0): data(dat), frequency(freq){};
            //TODO: oher RAII methods here

            char getData();
            void setLeftChild(std::shared_ptr<HuffmanNode>);
            void setRightChild(std::shared_ptr<HuffmanNode>);
            std::shared_ptr<HuffmanNode> getLeftChild();
            std::shared_ptr<HuffmanNode> getRightChild();
    };

    class HuffmanTree{
        private:
            std::shared_ptr<HuffmanNode> root;

        public:
            HuffmanTree(): root(nullptr){};
            //TODO: other RAII methods here

            void build(std::string data);
    };

}

#endif