#ifndef MYSQL_PROCESS_H
#define MYSQL_PROCESS_H

#include "io.h"
#include "table.h"

class Process {
private:
    vector<Table> database;
    vector<string> tableFileList; // contains all the filenames of the tables that are created before
    vector<string> tableNameList; // contains all the names of the tables that are created before
    string tableFileName;
    string tableNameFileName;
public:
    Process();
    Process(string& fileNameTableFile, string& fileNameTableName); // construct all tables from the given file
    ~Process();
    void createTableToFile(string& name, string& params, string& fileName);

    void testProcess(string s);

};

#endif
