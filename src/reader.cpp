#include <fstream>
#include <sstream>

#include "reader.h"

namespace ptlmuh006{
    using namespace std;


    string readFile(string filename){
        ostringstream outstr;

        ifstream infile(filename);
        std::string line;
        while(std::getline(infile, line)){
            outstr << line << "\n";
        }

        return outstr.str();
    }

}