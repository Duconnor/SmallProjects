#include "process.h"
#include <sstream>
#include <algorithm>

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

vector<vector<string> > Process::selectAll(string& name) {
    int index = find(name);
    vector<vector<string> > result;
    if (index == -1)
        return result;
    return database[index].select();
}

vector<vector<string> > Process::selectPart(string& name, string& columns) {
    int index = find(name);
    vector<vector<string> > result;
    if (index == -1)
        return result;
    return database[index].select(columns);
}

vector<vector<string> > Process::distinctIt(string& name, vector<vector<string> >& temp) {
    int index = find(name);
    return database[index].distinctSelect(temp);
}

vector<vector<string> > Process::orderIt(string& name, vector<vector<string> >& temp, string& whatOrder, string& columns) {
    int index = find(name);
    return database[index].orderSelect(temp, columns, whatOrder);
}

vector<vector<string> > Process::findRequire(string& name, vector<vector<string> >& temp, string& cols, string& vals) {
    int index = find(name);
    return database[index].requiredSelect(temp, cols, vals);
}

void Process::writeToFile(string& filename, vector<vector<string> >& temp) {
    File outfile(filename);
    outfile.writeTable(temp);
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

bool Process::updateProcess(vector<string>& columns, vector<string>& values, vector<string>& result, int start, int end) {
    // param end: the next pos behind the last elements
    string firstColumn = result[start];
    columns.push_back(firstColumn);
    start++;
    while (start < end - 2) {
        if (result[start] != "=")
            return false;
        start++;
        string temp = result[start];
        auto ite = std::find(temp.begin(), temp.end(), ',');
        if (ite == temp.end())
            return false;
        int index = std::distance(temp.begin(), ite);
        string val = temp.substr(0, index);
        string col = temp.substr(index + 1, temp.length() - index);
        columns.push_back(col);
        values.push_back(val);
        start++;
    }
    if (result[start] != "=")
        return false;
    start++;
    string lastValue = result[start];
    values.push_back(lastValue);
    return true;
}

void Process::applicationOn() {
    Input in;
    Output out;
    string s = "";
    while (true) {
        bool flag = false;
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
                flag = true;
            } else if (result[count++] == "TO") {
                // create table to file
                string filename = result[count++];
                if (count != result.size()) {
                    out.showText("Unknown order!");
                    continue;
                }
                createTableToFile(name, columns, filename);
                flag = true;
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
            flag = true;
        } else if (result[0] == "TABLE" && result[1] == "LIST") {
            vector<string> list = getTableList();
            out.showList(list);
            flag = true;
        } else if (result[0] == "INSERT" && result[1] == "INTO") {
            if (result.size() != 5 && result.size() != 6) {
                out.showText("Unknown order!");
                continue;
            }
            string name = result[2];
            if (result[3] == "VALUES" && result.size() == 5) {
                string values = result[4];
                insertInto(name, values);
                flag = true;
            } else if (result[4] == "VALUES" && result.size() == 6) {
                string columns = result[3];
                string values = result[5];
                insertInto(name, columns, values);
                flag = true;
            } else {
                out.showText("Unknown order!");
                continue;
            }
        } else if (result[0] == "DELETE") {
            if (result[1] == "FROM" && result.size() == 7 && result[3] == "WHERE" && result[5] == "=") {
                string name = result[2];
                string column = result[4];
                string value = result[6];
                deleteFrom(name, column, value);
                flag = true;
            } else if (result[1] == "*" && result.size() == 4 && result[2] == "FROM") {
                string name = result[3];
                deleteFrom(name);
                flag = true;
            }
        } else if (result[0] == "SELECT") {
            auto ite = std::find(result.begin(), result.end(), "FROM");
            string name, columns, cols, vals, orderCols, whatOrder, filename;
            bool distinct = false, order = false, where = false, to = false;
            if (ite == result.end()) {
                out.showText("Unknown order!");
                continue;
            } else
                name = *(ite + 1);
            ite = std::find(result.begin(), result.end(), "DISTINCT");
            if (ite == result.end()) {
                columns = result[1];
                distinct = false;
            } else {
                columns = *(ite + 1);
                distinct = true;
            }
            // search for key word "ORDER"
            ite = std::find(result.begin(), result.end(), "ORDER");
            if (ite == result.end())
                order = false;
            else {
                if (*(ite + 1) != "BY") {
                    out.showText("Unknown order!");
                    continue;
                } else {
                    order = true;
                    orderCols = *(ite + 2);
                    whatOrder = *(ite + 3);
                }
            }
            // search for key word "WHERE"
            ite = std::find(result.begin(), result.end(), "WHERE");
            if (ite == result.end())
                where = false;
            else {
                if (*(ite + 2) != "=") {
                    out.showText("Unknown order!");
                    continue;
                } else {
                    cols = *(ite + 1);
                    vals = *(ite + 3);
                    where = true;
                }
            }
            // search for key word "TO"
            ite = std::find(result.begin(), result.end(), "TO");
            if (ite == result.end())
                to = false;
            else {
                filename = *(ite + 1);
                to = true;
            }
            // now process
            vector<vector<string> > result;
            if (columns == "*") {
                result = selectAll(name);
                if (result.size() == 0) {
                    out.showText("No match!");
                    continue;
                }
                flag = true;
            }
            else {
                result = selectPart(name, columns);
                if (result.size() == 0) {
                    out.showText("No match!");
                    continue;
                }
                flag = true;
            }
            if (distinct) {
                result = distinctIt(name, result);
                if (result.size() == 0) {
                    out.showText("No match!");
                    continue;
                }
                flag = true;
            }
            if (order) {
                result = orderIt(name, result, whatOrder, orderCols);
                if (result.size() == 0) {
                    out.showText("No match!");
                    continue;
                }
                flag = true;
            }
            if (where) {
                result = findRequire(name, result, cols, vals);
                if (result.size() == 0) {
                    out.showText("No match!");
                    continue;
                }
                flag = true;
            }
            out.showTable(result);
            if (to) {
                writeToFile(filename, result);
                flag = true;
            }
        } else if (result[0] == "UPDATE") {
            string name = result[1];
            if (result[2] != "SET") {
                out.showText("Unknown order!");
                continue;
            }
            bool where = false;
            string cols, vals;
            int end = result.size();
            auto ite = std::find(result.begin(), result.end(), "WHERE");
            if (ite == result.end())
                where = false;
            else {
                if (*(ite + 2) != "=") {
                    out.showText("Unknown order!");
                    continue;
                } else {
                    cols = *(ite + 1);
                    vals = *(ite + 3);
                    where = true;
                    end = std::distance(result.begin(), ite);
                }
            }
            // now process
            vector<string> columns;
            vector<string> values;
            if (!updateProcess(columns, values, result, 3, end)) {
                out.showText("Unknown order!");
                continue;
            }
            if (where) {
                update(name, columns, values, cols, vals);
                flag = true;
            }
            else {
                update(name, columns, values);
                flag = true;
            }
        } else
            if (!flag)
                out.showText("Unknown Order");
    }
}
