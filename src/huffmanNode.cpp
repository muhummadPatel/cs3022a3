#include <memory>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    char HuffmanNode::getData(){
        return data;
    }

    int HuffmanNode::getFrequency(){
        return frequency;
    }

    void HuffmanNode::setData(char newData){
        data = newData;
    }

    void HuffmanNode::setFrequency(int newFrequency){
        frequency = newFrequency;
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

    //TODO: make this static?
//    bool HuffmanNode::compare(HuffmanNode one, HuffmanNode other){
//        return (one.frequency < other.frequency);
//    }

}