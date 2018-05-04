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

    int find(string& name); // return the index of the table
    bool createTableToFile(string& name, string& params, string& fileName);
    bool createTableFromFile(string& name, string& fileName);
    bool dropTable(string& name);
    vector<string> getTableList();
    bool insertInto(string& name, string& values);
    bool insertInto(string& name, string& columns, string& values);
    bool deleteFrom(string& name, string& column, string& value);
    bool deleteFrom(string& name);
    bool update(string& name, vector<string>& columns, vector<string>& values);
    bool update(string& name, vector<string>& columns, vector<string>& values, string& column, string& value);
    bool selectPart(string& name, string& columns);
    bool selectAll(string& name);
    bool selectDistinctPart(string& name, string& columns);
    bool selectDistinctAll(string& name);
    bool selectOrderPart(string& name, string& columns, string& cols, string& whatOrder);
    bool selectOrderAll(string& name, string& cols, string& whatOrder);
    bool selectRequirePart(string& name, string& columns, string& column, string& value);
    bool selectRequireAll(string& name, string& column, string& value);
    bool selectPartToFile(string& name, string& columns, string& filename);
    bool selectAllToFile(string& name, string& filename);

    vector<string> splitBySpace(string& s);
public:
    Process();
    Process(string& fileNameTableFile, string& fileNameTableName); // construct all tables from the given file
    ~Process();
    void applicationOn();


};

#endif
