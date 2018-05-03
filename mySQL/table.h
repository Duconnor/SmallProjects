#ifndef MYSQL_VECSTR_H
#define MYSQL_VECSTR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#endif

#ifndef MYSQL_TABLE_H
#define MYSQL_TABLE_H

#include <set>
using std::set;

class Table {
private:
    string name;
    vector<vector<string> > table;

    vector<string> processString(string& s);
    vector<string> processCommaString(string& s);
    vector<int> findMatch(vector<string>& constraints); // find the index of the match elements in the table
public:
    Table();
    Table(vector<vector<string> >& input, string& name); // initial a table from file
    Table(string& params, string& name); // create an empty table
    Table(const Table& that);
    const vector<vector<string> >& getTable() const;
    string getName() const;
    void insert(string& values); // insert full values
    void insert(string& columns, string& values); // insert values indicated by columns name
    void remove(string& column, string& value); // delete rows whose column matches value
    void remove(); // delete all rows in the table
    void update(vector<string>& columns, vector<string>& values); // update information in the given columns
    void update(vector<string>& columns, vector<string>& values, string& colConstraints, string& valConstraints);\
        // update the information in the asked row
    vector<vector<string> > select(string& s); // return the asked columns
    vector<vector<string> >& select(); // return the whole table
    vector<vector<string> > distinctSelect(vector<vector<string> >& temp); // return the distinct values
    vector<vector<string> > requiredSelect(vector<vector<string> >& temp, string& column, string& value);\
        // return only the asked row
    vector<vector<string> > orderSelect(vector<vector<string> >& temp, string& columns, string& whatOrder); \
        // display the table in asked order according to the given columns
};

#endif
