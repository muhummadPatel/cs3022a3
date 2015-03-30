#include <unordered_map>
#include <sstream>
#include <iostream>

#include "huffman.h"

namespace ptlmuh006{

    using namespace std;

    void HuffmanTree::build(std::string data){
        //TODO: split these up into seperate private methods?
        //counting occurrences
        unordered_map<char, int> freqTbl;
        for(int i = 0; i < data.length(); i++){
            //cout << data[i] << endl;

            auto res = freqTbl.find(data[i]);
            if(res == freqTbl.end()){
                //new character found so instert with count = 1
                freqTbl.insert({data[i], 1});
            }else{
                //already exists, so update the count
                freqTbl[data[i]] = freqTbl.at(data[i]) + 1;
            }
        }

//        for(auto it = freqTbl.begin(); it != freqTbl.end(); ++it){
//            cout << it->first << " occurs " << it->second << " times" << endl;
//        }

        
    }

}