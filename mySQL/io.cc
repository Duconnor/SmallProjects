#include "io.h"
#include <string.h>
#include <iostream>
#include <fstream>

const int MAXSIZE = 10000;

vector<string> File::readLine() {
    vector<string> tableName;
    char line[MAXSIZE];
    std::ifstream infile(filename,std::ios::in);

    // error handling
    if(!infile.is_open()) {
        std::cout << "open file error!" << std::endl;
        infile.clear();
        infile.close();
        return tableName;
    }

    infile.getline(line, MAXSIZE);
    char *s = nullptr;
    char delim[] = {" "};
    s = strtok(line, delim);
    while(s!=nullptr) {
        string name(s);
        tableName.push_back(name);
        s = strtok(nullptr, delim);
    }
    infile.clear();
    infile.close();
}

vector<vector<string>> File::readTable() {
    vector<string> firstLine = readLine();
    vector<vector<string>> table;
    table.push_back(firstLine);
    std::ifstream infile(filename, std::ios::in);
    if(!infile.is_open()) {
        std::cout << "open file error!" << std::endl;
        infile.clear();
        infile.close();
        return table;
    }
    char s[MAXSIZE]
    infile.getline(s," ");
    int size = firstLine.size(), int count = 0;
    string buffer;
    vector<string> oneLine;
    while(infile >> buffer) {
        oneLine.push_back(buffer);
        count++; // count is the number of information in this line
        if(count == size) {
            // this line is finished
            table.push_back(oneLine);
            oneLine.clear();
            count = 0;
        }
    }
    infile.clear();
    infile.close();
    return table;
}

int main() {
    // test
    File file("")
    return 0;
}
