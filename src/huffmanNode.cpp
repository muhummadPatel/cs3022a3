/*
 * HuffmanNode class implementation. This class models the Nodes used to build the HuffmanTree. Each node stores a
 * character (internal nodes have no character), and the frequency (# of times the character appeared in the data).
 * The class also contains accessor and mutator methods to allow the tree to manipulate the nodes as neccessary.
 * A static compareNodes method is also provided that compares two nodes and is used to order the nodes in the priority
 * queue used in the HuffmanTree class.
 *
 * Muhummad Patel
 * 07-Apr-2015
 */

#include <memory>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    //copy constructor
    HuffmanNode::HuffmanNode(const HuffmanNode& other){
        data = other.data;
        frequency = other.frequency;
        leftChild = other.leftChild;
        rightChild = other.rightChild;
    }

    //move constructor
    HuffmanNode::HuffmanNode(HuffmanNode&& other){
        data = other.data;
        frequency = other.frequency;
        leftChild = other.leftChild;
        rightChild = other.rightChild;

        other.data = '\0';
        other.frequency = 0;
        other.leftChild = nullptr;
        other.rightChild = nullptr;
    }

    //destructor
    HuffmanNode::~HuffmanNode(){
    }

    //copy assignment
    HuffmanNode& HuffmanNode::operator= (const HuffmanNode& rhs){
        data = rhs.data;
        frequency = rhs.frequency;
        leftChild = rhs.leftChild;
        rightChild = rhs.rightChild;

        return *this;
    }

    //move assignment
    HuffmanNode& HuffmanNode::operator= (HuffmanNode&& rhs){
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

    bool HuffmanNode::compareNodes(shared_ptr<HuffmanNode> one, shared_ptr<HuffmanNode> other){
        return (one->getFrequency() > other->getFrequency());
    }
}