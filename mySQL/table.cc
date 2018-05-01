#include "table.h"

vector<string> Table::processString(string& s) {
    vector<string> words;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '('|| s[i] == ')')
            continue;
        else {
            int j = i + 1;
            while (j < s.length()) {
                if (s[j] == ')' || s[j] == ',')
                    break;
                j++;
            }
            string word = s.substr(i, j - i);
            words.push_back(word);
            i = j;
        }
    }
    return words;
}

vector<int> Table::findMatch(vector<string>& constraints) {
    int size = constraints.size();
    vector<int> index(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < table[0].size(); j++)
            if (constraints[i] == table[0][j]) {
                index[i] = j;
                break;
            }
    return index;
}

Table::Table(vector<vector<string>>& input, string& name) {
    this->name = name;
    for (auto l:input) {
        vector<string> line;
        for (auto i:l)
            line.push_back(i);
        table.push_back(line);
    }
}

vector<vector<string>>& Table::getTable() {
    return table;
}

string Table::getName() {
    return name;
}

void Table::insert(string& values) {
    vector<string> newLine = processString(values);
    table.push_back(newLine);
}

void Table::insert(string& columns, string& values) {
    vector<string> columnsWords = processString(columns);
    vector<string> valuesWords = processString(values);
    int size = columnsWords.size();
    vector<int> index = findMatch(columnsWords);
    vector<string> newLine(size, "");
    for (int i = 0; i < size; i++)
        newLine[index[i]] = valuesWords[i];
    table.push_back(newLine);
}

void Table::remove(string& column, string& value) {
    vector<string> col(1, column);
    vector<int> index = findMatch(col);
    auto ite = table.begin();
    for (; ite != table.end(); ite++)
        if ((*ite).at(index[0]) == value)
            break;
    if (ite == table.end())
        return;
    table.erase(ite);
}

void Table::remove() {
    auto iteStart = table.begin() + 1;
    auto iteEnd = table.end();
    table.erase(iteStart, iteEnd);
}

void Table::update(vector<string>& columns, vector<string>& values) {
    vector<int> index = findMatch(columns);
    for (int i = 1; i < table.size(); i++)
        for (int j = 0; j < index.size(); j++)
            table[i][index[j]] = values[j];
}

void Table::update(vector<string>& columns, vector<string>& values, string& colConstraints, string& valConstraints) {
    vector<int> index = findMatch(columns);
    vector<string> col(1, colConstraints);
    vector<int> indexConstraints = findMatch(col);
    for (int i = 1; i < table.size(); i++)
        if (table[i][indexConstraints[0]] == valConstraints) {
            // find the matched line
            for (int j = 0; j < index.size(); j++)
                table[i][index[j]] = values[j];
        }
}
