#ifndef MYSQL_VECSTR_H
#define MYSQL_VECSTR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#endif

#ifndef MYSQL_TABLE_H
#define MYSQL_TABLE_H

class Table {
private:
    string name;
    vector<vector<string>> table;

    vector<string> processString(string& s);
    vector<int> findMatch(vector<string>& constraints); // find the index of the match elements in the table
public:
    Table();
    Table(vector<vector<string>>& input, string& name); // initial a table from file
    vector<vector<string>>& getTable();
    string getName();
    void insert(string& values); // insert full values
    void insert(string& columns, string& values); // insert values indicated by columns name
    void remove(string& column, string& value); // delete rows whose column matches value
    void remove(); // delete all rows in the table
    void update(vector<string>& columns, vector<string>& values); // update information in the given columns
    void update(vector<string>& columns, vector<string>& values, string& colConstraints, string& valConstraints); // update the\
    information in the asked row
};

#endif
