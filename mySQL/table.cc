#include "table.h"
#include <algorithm>

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

vector<string> Table::processCommaString(string& s) {
    vector<string> result;
    for (int i = 0; i < s.length(); i++) {
        int j = i +1;
        while (j < s.length()) {
            if (s[j] == ',')
                break;
            j++;
        }
        string temp = s.substr(i, j - i);
        result.push_back(temp);
        i = j;
    }
    return result;
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

Table::Table(vector<vector<string> >& input, string& name) {
    this->name = name;
    for (auto l:input) {
        vector<string> line;
        for (auto i:l)
            line.push_back(i);
        table.push_back(line);
    }
}

Table::Table(string& params, string& name) {
    this->name = name;
    vector<string> firstLine = processString(params);
    table.push_back(firstLine);
}

Table::Table(const Table& that) {
    name = that.getName();
    vector<vector<string> > thatTable = that.getTable();
    for (auto line: thatTable)
        table.push_back(line);
}

const vector<vector<string> >& Table::getTable() const {
    return table;
}

string Table::getName() const {
    return name;
}

bool Table::insert(string& values) {
    vector<string> newLine = processString(values);
    if (newLine.size() != getColNum())
        return false;
    table.push_back(newLine);
    return true;
}

bool Table::insert(string& columns, string& values) {
    vector<string> columnsWords = processString(columns);
    vector<string> valuesWords = processString(values);
    if (columnsWords.size() != valuesWords.size())
        return false;
    int size = columnsWords.size();
    vector<int> index = findMatch(columnsWords);
    vector<string> newLine(size, "");
    for (int i = 0; i < size; i++)
        newLine[index[i]] = valuesWords[i];
    table.push_back(newLine);
    return true;
}

bool Table::remove(string& column, string& value) {
    vector<string> col(1, column);
    vector<int> index = findMatch(col);
    auto ite = table.begin();
    for (; ite != table.end(); ite++)
        if ((*ite).at(index[0]) == value)
            break;
    if (ite == table.end())
        return false;
    table.erase(ite);
    return true;
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

vector<vector<string> > Table::select(string& s) {
    vector<string> columns = processCommaString(s);
    vector<vector<string> > result;
    vector<int> index = findMatch(columns);
    for (auto line: table) {
        vector<string> newLine;
        for (auto i: index)
            newLine.push_back(line[i]);
        result.push_back(newLine);
    }
    return result;
}

vector<vector<string> >& Table::select() {
    return table;
}

vector<vector<string> > Table::distinctSelect(vector<vector<string> >& temp) {
    set<vector<string> > setVector;
    vector<vector<string> > result;
    for (auto line: temp)
        if (setVector.find(line) == setVector.end()) {
            // not appeared before
            result.push_back(line);
            setVector.insert(line);
        }
    return result;
}

vector<vector<string> > Table::requiredSelect(vector<vector<string> >& temp, string& column, string& value) {
    vector<string> constraints(1, column);
    vector<int> index = findMatch(constraints);
    vector<vector<string> > result;
    result.push_back(temp[0]);
    for (int i = 1; i < temp.size(); i++)
        if (table[i][index[0]] == value)
            result.push_back(temp[i]);
    return result;
}

vector<vector<string> > Table::orderSelect(vector<vector<string> >&temp, string& columns, string& whatOrder) {
    vector<string> col = processCommaString(columns);
    vector<int> index = findMatch(col);
    vector<vector<string> > result(temp);
    vector<int> corresIndex;
    for (int i = 0; i < temp.size(); i++)
        corresIndex.push_back(i);
    for (int i = index.size() - 1; i >= 0; i--) {
        // sort according to this column
        for (int j = 1; j < result.size() - 1; j++) {
            int k = j + 1;
            while (k > 1 && table[corresIndex[k - 1]][index[i]] > table[corresIndex[k]][index[i]]) {
                vector<string> t = result[k - 1];
                result[k - 1] = result[k];
                result[k] = t;
                int val = corresIndex[k - 1];
                corresIndex[k - 1] = corresIndex[k];
                corresIndex[k] = val;
                k--;
            }
        }
    }
    if (whatOrder == "ASC")
        return result;
    else {
        reverse(result.begin() + 1, result.end());
        return result;
    }
}
