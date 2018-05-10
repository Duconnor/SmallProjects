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
    vector<vector<string> > selectAll(string& name);
    vector<vector<string> > selectPart(string& name, string& columns);
    vector<vector<string> > distinctIt(string& name, vector<vector<string> >& temp);
    vector<vector<string> > orderIt(string& name, vector<vector<string> >& temp, string& whatOrder, string& columns);
    vector<vector<string> > findRequire(string& name, vector<vector<string> >& temp, string& cols, string& vals);
    vector<vector<string> > findMax(string& name, vector<vector<string> >& temp, string& col);
    void writeToFile(string& filename, vector<vector<string> >& temp);
    void showLegalOrder();

    vector<string> splitBySpace(string& s);
    bool updateProcess(vector<string>& columns, vector<string>& values, vector<string>& result, int start, int end);
    bool isLegal(string& order);
    bool performOrder(string& order);
    void doWhatFileSays(vector<string>& orders);
public:
    Process();
    Process(string& fileNameTableFile, string& fileNameTableName); // construct all tables from the given file
    ~Process();
    void applicationOn();
};

#endif
