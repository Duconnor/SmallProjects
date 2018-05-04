#include "process.h"
#include <sstream>

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

int Process::find(string& name) {
    for (int i = 0; i < tableNameList.size(); i++)
        if (tableNameList[i] == name)
            return i;
    Output out;
    out.showText("No such table!");
    return -1;
}

bool Process::createTableToFile(string& name, string& params, string& fileName) {
    // params has the form: (xxx,xxx,xxx)
    Output out;
    for (auto Tname: tableNameList)
        if (Tname == name) {
           out.showText("Name being occupied!");
           return false;
        }
    for (auto Fname: tableFileList)
        if (Fname == fileName) {
            out.showText("File name being occupied!");
            return false;
        }

    // now we are ready to create this table
    Table table(params, name);
    database.push_back(table);
    tableFileList.push_back(fileName);
    tableNameList.push_back(name);
    out.showTable(table.getTable());
    return true;
}

bool Process::createTableFromFile(string& name, string& fileName) {
    Output out;
    for (auto Tname: tableNameList)
        if (Tname == name) {
           out.showText("Name being occupied!");
           return false;
        }
    for (auto Fname: tableFileList)
        if (Fname == fileName) {
            out.showText("File name already being used!");
            return false;
        }

    File file(fileName);
    vector<vector<string> > input = file.readTable();
    Table table(input, name);
    database.push_back(table);
    tableFileList.push_back(fileName);
    tableNameList.push_back(name);
    out.showTable(input);
    return true;
}

bool Process::dropTable(string& name) {
    int index = -1;
    for (int i = 0; i < tableNameList.size(); i++)
        if (tableNameList[i] == name) {
            index = i;
            break;
        }
    if (index == -1) {
        Output out;
        out.showText("Could not find this table!");
        return false;
    }
    database.erase(database.begin() + index);
    tableNameList.erase(tableNameList.begin() + index);
    tableFileList.erase(tableFileList.begin() + index);
}

vector<string> Process::getTableList() {
    vector<string> result;
    for (int i = 0; i < database.size(); i++) {
        string s = tableNameList[i];
        s = s + ":";
        std::stringstream strStream;
        int colNum = database[i].getColNum();
        int rowNum = database[i].getRowNum();
        strStream << colNum;
        string col, row;
        strStream >> col;
        strStream.str("");
        strStream.clear();
        strStream << rowNum;
        strStream >> row;
        strStream.str("");
        s = s + "(" + col + "," + row + ")" + "[";
        vector<string> tableHead = database[i].getTableHead();
        for (int j = 0; j < tableHead.size(); j++) {
            if (j == tableHead.size() - 1)
                s += tableHead[j] + "]";
            else
                s += tableHead[j] + ",";
        }
        result.push_back(s);
    }
    return result;
}

bool Process::insertInto(string& name, string& values) {
    int index = find(name);
    if (index == -1)
        return false;
    if (!database[index].insert(values))
        return false;
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::insertInto(string& name, string& columns, string& values) {
    int index = find(name);
    if (index == -1 || !database[index].insert(columns, values))
        return false;
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::deleteFrom(string& name, string& column, string& value) {
    int index = find(name);
    if (index == -1 || !database[index].remove(column, value))
        return false;
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::deleteFrom(string& name) {
    int index = find(name);
    if (index == -1)
        return false;
    database[index].remove();
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::update(string& name, vector<string>& columns, vector<string>& values) {
    int index = find(name);
    if (index == -1)
        return false;
    database[index].update(columns, values);
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::update(string& name, vector<string>& columns, vector<string>& values, string& column, string& value) {
    int index = find(name);
    if (index == -1)
        return false;
    database[index].update(columns, values, column, value);
    Output out;
    out.showTable(database[index].getTable());
    return true;
}

bool Process::selectPart(string& name, string& columns) {
    int index = find(name);
    if (index == -1)
        return false;
    Output out;
    out.showTable(database[index].select(columns));
    return true;
}

bool Process::selectAll(string& name) {
    int index = find(name);
    if (index == -1)
        return false;
    Output out;
    out.showTable(database[index].select());
    return true;
}

bool Process::selectDistinctPart(string& name, string& columns) {
    int index = find(name);
    if (index == -1)
        return false;
    Output out;
    vector<vector<string> > temp = database[index].select(columns);
    out.showTable(database[index].distinctSelect(temp));
    return true;
}

bool Process::selectDistinctAll(string& name) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select();
    Output out;
    out.showTable(database[index].distinctSelect(temp));
    return true;
}

bool Process::selectOrderPart(string& name, string& columns, string& cols, string& whatOrder) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select(columns);
    Output out;
    out.showTable(database[index].orderSelect(temp, cols, whatOrder));
    return true;
}

bool Process::selectOrderAll(string& name, string& cols, string& whatOrder) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select();
    Output out;
    out.showTable(database[index].orderSelect(temp, cols, whatOrder));
    return true;
}

bool Process::selectRequirePart(string& name, string& columns, string& column, string& value) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select(columns);
    Output out;
    out.showTable(database[index].requiredSelect(temp, column, value));
    return true;
}

bool Process::selectRequireAll(string& name, string& column, string& value) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select();
    Output out;
    out.showTable(database[index].requiredSelect(temp, column, value));
    return true;
}

bool Process::selectPartToFile(string& name, string& columns, string& filename) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select(columns);
    File outfile(filename);
    outfile.writeTable(temp);
    Output out;
    out.showTable(temp);
    return true;
}

bool Process::selectAllToFile(string& name, string& filename) {
    int index = find(name);
    if (index == -1)
        return false;
    vector<vector<string> > temp = database[index].select();
    File outfile(filename);
    outfile.writeTable(temp);
    Output out;
    out.showTable(temp);
    return true;
}

vector<string> Process::splitBySpace(string& s) {
    vector<string> result;
    for (int i = 0; i < s.length(); i++) {
        int j = i + 1;
        while (j < s.length()) {
            if (s[j] == ' ')
                break;
            j++;
        }
        string temp = s.substr(i, j - i);
        i = j;
        result.push_back(temp);
    }
    return result;
}

void Process::applicationOn() {
    Input in;
    Output out;
    string s = "";
    while (true) {
        out.showMenu();
        s = in.getString();
        if (s == "quit")
            break;
        vector<string> result = splitBySpace(s);
        if (result.size() < 2) {
            out.showText("Unknown order!");
            continue;
        }
        if (result[0] == "CREATE" && result[1] == "TABLE") {
            // create table family
            if (result.size() != 5 && result.size() != 6) {
                out.showText("Unknown order!");
                continue;
            }
            int count = 2;
            string name = result[count++];
            string columns = result[count++];
            if (columns == "FROM") {
                // create table from file
                string filename = result[count++];
                if (count != result.size()) {
                    out.showText("Unknown order!");
                    continue;
                }
                createTableFromFile(name, filename);
            } else if (result[count++] == "TO") {
                // create table to file
                string filename = result[count++];
                if (count != result.size()) {
                    out.showText("Unknown order!");
                    continue;
                }
                createTableToFile(name, columns, filename);
            } else {
                out.showText("Unknown order!");
                continue;
            }
        } else if (result[0] == "DROP" && result[1] == "TABLE") {
            if (result.size() == 2) {
                out.showText("Unknown order!");
                continue;
            }
            dropTable(result[2]);
        } else if (result[0] == "TABLE" && result[1] == "LIST") {
            vector<string> list = getTableList();
            out.showList(list);
        } else if (result[0] == "INSERT" && result[1] == "INTO") {
            if (result.size() != 5 && result.size() != 6) {
                out.showText("Unknown order!");
                continue;
            }
            string name = result[2];
            if (result[3] == "VALUES" && result.size() == 5) {
                string values = result[4];
                insertInto(name, values);
            } else if (result[4] == "VALUES" && result.size() == 6) {
                string columns = result[3];
                string values = result[5];
                insertInto(name, columns, values);
            } else {
                out.showText("Unknown order!");
                continue;
            }
        }
    }
}

