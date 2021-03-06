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
    vector<int> index(size, -1);
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
    vector<string> newLine;
    int count = 0;
    for (int i = 0; i < getColNum(); i++) {
        auto ite = std::find(index.begin(), index.end(), i);
        if (ite == index.end())
            newLine.push_back(" ");
        else
            newLine.push_back(valuesWords[distance(index.begin(), ite)]);
    }
    table.push_back(newLine);
    return true;
}

bool Table::remove(string& column, string& value) {
    vector<string> col(1, column);
    vector<int> index = findMatch(col);
    if (index[0] == -1)
        return false;
    bool flag = false;
    auto ite = table.begin();
    for (; ite != table.end(); ) {
        if ((*ite).at(index[0]) == value) {
            ite = table.erase(ite);
            flag = true;
        }
        else
            ite++;
    }
    if (!flag)
        return flag;
    return true;
}

void Table::remove() {
    auto iteStart = table.begin() + 1;
    auto iteEnd = table.end();
    table.erase(iteStart, iteEnd);
}

bool Table::update(vector<string>& columns, vector<string>& values) {
    vector<int> index = findMatch(columns);
    for (auto i: index)
        if (i == -1)
            return false;
    for (int i = 1; i < table.size(); i++)
        for (int j = 0; j < index.size(); j++)
            table[i][index[j]] = values[j];
    return true;
}

bool Table::update(vector<string>& columns, vector<string>& values, string& colConstraints, string& valConstraints) {
    vector<int> index = findMatch(columns);
    vector<string> col(1, colConstraints);
    vector<int> indexConstraints = findMatch(col);
    for (auto i: index)
        if (i == -1)
            return false;
    for (auto i: indexConstraints)
        if (i == -1)
            return false;
    for (int i = 1; i < table.size(); i++)
        if (table[i][indexConstraints[0]] == valConstraints) {
            // find the matched line
            for (int j = 0; j < index.size(); j++)
                table[i][index[j]] = values[j];
        }
    return true;
}

vector<vector<string> > Table::select(string& s) {
    vector<string> columns = processCommaString(s);
    vector<vector<string> > result;
    vector<int> index = findMatch(columns);
    if (index[0] == -1)
        return result;
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
    if (whatOrder == "DESC")
        return result;
    else {
        reverse(result.begin() + 1, result.end());
        return result;
    }
}

vector<vector<string> > Table::maxSelect(vector<vector<string> >& temp, string& column) {
    vector<string> col;
    col.push_back(column);
    vector<int> index = findMatch(col);
    vector<vector<string> > result;
    if (temp.size() <= 1 || index[0] == -1)
        return result;
    int maxIndex = 1;
    for (int i = 2; i < temp.size(); i++) {
        if (table[i][index[0]].length() > table[maxIndex][index[0]].length())
            maxIndex = i;
        else if (table[i][index[0]].length() == table[maxIndex][index[0]].length())
            if (table[i][index[0]] > table[maxIndex][index[0]])
                maxIndex = i;
    }
    result.push_back(table[maxIndex]);
    return result;
}
