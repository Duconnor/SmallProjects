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
    vector<vector<string>> readTable();
};

#endif
