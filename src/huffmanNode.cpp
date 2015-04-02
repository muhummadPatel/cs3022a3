#include <memory>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    HuffmanNode::HuffmanNode(const HuffmanNode& other){
        //copy constructor
        data = other.data;
        frequency = other.frequency;
        leftChild = other.leftChild;
        rightChild = other.rightChild;
    }

    HuffmanNode::HuffmanNode(HuffmanNode&& other){
        //move constructor
        data = other.data;
        frequency = other.frequency;
        leftChild = other.leftChild;
        rightChild = other.rightChild;

        other.data = '\0';
        other.frequency = 0;
        other.leftChild = nullptr;
        other.rightChild = nullptr;
    }

    HuffmanNode::~HuffmanNode(){
        //destructor
        //TODO: anything to put here really?
    }

    HuffmanNode& HuffmanNode::operator= (const HuffmanNode& rhs){
        //copy assignment
        data = rhs.data;
        frequency = rhs.frequency;
        leftChild = rhs.leftChild;
        rightChild = rhs.rightChild;

        return *this;
    }

    HuffmanNode& HuffmanNode::operator= (HuffmanNode&& rhs){
        //move assignment
        data = rhs.data;
        frequency = rhs.frequency;
        leftChild = rhs.leftChild;
        rightChild = rhs.rightChild;

        rhs.data = '\0';
        rhs.frequency = 0;
        rhs.leftChild = nullptr;
        rhs.rightChild = nullptr;

        return *this;
    }

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