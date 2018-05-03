#include "process.h"

Process::Process(string& fileNameTableFile, string& fileNameTableName) {
    File fileTable(fileNameTableFile);
    tableFileList = fileTable.readLine();
    File fileName(fileNameTableName);
    tableNameList = fileName.readLine();
    int count = 0;
    for (auto name: tableFileList) {
        File inFile(name);
        vector<vector<string> > input = inFile.readTable();
        int i = 0;
        while (i < name.size()) {
            if (name[i] == '.')
                break;
            i++;
        }
        string tableName = tableNameList[count];
        Table table(input, tableName);
        database.push_back(table);
        count++;
    }
    tableFileName = fileNameTableFile;
    tableNameFileName = fileNameTableName;
}

Process::~Process() {
    File fileTable(tableFileName);
    fileTable.writeLine(tableFileList);
    File fileName(tableNameFileName);
    fileName.writeLine(tableNameList);
    int count = 0;
    for (auto table: database) {
        string s = tableFileList[count];
        File outfile(s);
        outfile.writeTable(table.getTable());
        count++;
    }
}

void Process::createTableToFile(string& name, string& params, string& fileName) {
    // params has the form: (xxx,xxx,xxx)
    Output out;
    for (auto Tname: tableNameList)
        if (Tname == name) {
           out.showText("Name being occupied!");
           return;
        }
    for (auto Fname: tableFileList)
        if (Fname == fileName) {
            out.showText("File name being occupied!");
            return;
        }

    // now we are ready to create this table
    Table table(params, name);
    database.push_back(table);
    tableFileList.push_back(fileName);
    tableNameList.push_back(name);
}

void Process::testProcess(string s) {
    vector<vector<string> > r;
    vector<vector<string> > r1;
    for (auto table:database) {
        if (table.getName() == s) {
            string s1 = "Name,Major";
            string s2 = "Name,ID";
            string s3 = "DESC";
            r = table.select(s1);
            r1 = table.orderSelect(r, s2, s3);
            break;
        }
    }
    Output out;
    out.showTable(r1);
}

