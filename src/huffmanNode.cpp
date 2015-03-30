#include <memory>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    char HuffmanNode::getData(){
        return data;
    }

    void HuffmanNode::setLeftChild(shared_ptr<HuffmanNode> newLeft){
        leftChild = newLeft;
    }

    void HuffmanNode::setRightChild(shared_ptr<HuffmanNode> newRight){
            rightChild = newRight;
    }

    shared_ptr<HuffmanNode> HuffmanNode::getLeftChild(){
        return leftChild;
    }

    shared_ptr<HuffmanNode> HuffmanNode::getRightChild(){
            return rightChild;
    }

}