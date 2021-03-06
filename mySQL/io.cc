#include "io.h"
#include <string.h>
#include <iostream>
#include <iomanip>
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
    return tableName;
}

vector<string> File::readLineByLine() {
    vector<string> result;
    std::ifstream infile(filename,std::ios::in);

    if (!infile.is_open()) {
        std::cout << "open file error!" << std::endl;
        infile.clear();
        infile.close();
        return result;
    }

    string line;
    while(getline(infile, line))
        result.push_back(line);
    infile.clear();
    infile.close();
    return result;
}

vector<vector<string> > File::readTable() {
    vector<string> firstLine = readLine();
    vector<vector<string> > table;
    table.push_back(firstLine);
    std::ifstream infile(filename, std::ios::in);
    if(!infile.is_open()) {
        std::cout << "open file error!" << std::endl;
        infile.clear();
        infile.close();
        return table;
    }
    char buffer[MAXSIZE];
    infile.getline(buffer, MAXSIZE);
    int size = firstLine.size();
    vector<string> oneLine;
    while(infile.getline(buffer, MAXSIZE)) {
        char *s = nullptr;
        char delim[] = {" "};
        s = strtok(buffer, delim);
        while(s!=nullptr) {
            string temp(s);
            oneLine.push_back(temp);
            s = strtok(nullptr, delim);
    }

        if(oneLine.size() <= size) {
            // this line is finished
            table.push_back(oneLine);
            oneLine.clear();
        }
    }
    infile.clear();
    infile.close();
    return table;
}

void File::writeLine(const vector<string>& line) {
    std::ofstream outfile (filename, std::ios::out);
    if(!outfile.is_open()) {
        std::cout << "open file error!" << std::endl;
        outfile.clear();
        outfile.close();
        return;
    }
    for(auto s: line)
        outfile << s << " ";
    outfile << std::endl;
    outfile.clear();
    outfile.close();
}

void File::writeTable(const vector<vector<string> >& table) {
    std::ofstream outfile (filename, std::ios::out);
    if(!outfile.is_open()) {
        std::cout << "open file error!" << std::endl;
        outfile.clear();
        outfile.close();
        return;
    }
    for (auto i: table) {
        for (auto j: i)
            outfile << j << " ";
        outfile << std::endl;
    }
    outfile.clear();
    outfile.close();
}

void Output::showMenu() {
    std::cout << "(mysql)==>";
}

void Output::showTable(const vector<vector<string> >& table) {
    int num = table[0].size();
    string delim = "---------------";
    string frame;
    for (int i = 0;i< num + 1 ;i++)
        frame.append(delim);
    std::cout << frame << std::endl;
    int count = 0;
    for (auto line:table) {
        if (count == 0)
            std::cout << std::left << std::setw(12) << "ID";
        else
            std::cout << std::left << std::setw(12) << count;
        count++;
        for (auto s:line)
            std::cout << std::left << std::setw(12) << s;
        std::cout << std::endl;
    }
    std::cout << frame << std::endl;
}

void Output::showList(const vector<string>& list) {
    int total = list.size();
    std::cout << "\ttotal " << total << std::endl;
    for (auto line:list) {
        std::cout << "\t\t";
        std::cout << line;
        std::cout << std::endl;
    }
}

void Output::showText(string text) {
    std::cout << text << std::endl;
}

string Input::getString() {
    string s;
    std::cin.clear();
    std::getline(std::cin, s);
    return s;
}
