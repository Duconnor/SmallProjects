#ifndef MYSQL_VECSTR_H
#define MYSQL_VECSTR_H
#include <vector>
#include <string>

using std::vector;
using std::string;

#endif

#ifndef MYSQL_IO_H
#define MYSQL_IO_H

// class File: read data from file
class File {
private:
    string filename; // the data file name
public:
    File();
    File(string filename) {this->filename = filename;};
    vector<string> readLine(); // read one line and separate the word by space
    vector<vector<string> > readTable();
    void writeLine(const vector<string>& line); // write the contents in a single line
    void writeTable(const vector<vector<string> >& table); // write the content in the table to the file
};


// class Output: standard output
class Output {
public:
    void showMenu();
    void showTable(const vector<vector<string> >& table);
    void showList(const vector<string>& list);
    void showText(string text);
};


// class Input: standard input
class Input {
public:
    string getString();
};

#endif
