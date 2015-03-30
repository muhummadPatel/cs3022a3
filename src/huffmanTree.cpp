#include <unordered_map>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    std::unordered_map<char, std::string> codeTbl;

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

}