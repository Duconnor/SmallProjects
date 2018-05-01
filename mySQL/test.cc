#include "table.h"
#include "io.h"

int main() {
    File infile("student.txt");
    Output out;
    vector<vector<string>> input = infile.readTable();
    string s1 = "student";
    Table table(input, s1);
    vector<vector<string>> t = table.getTable();
    out.showTable(t);
    vector<string> columns = {"Major"};
    vector<string> values = {"Physic"};
    string s2 = "Major";
    string s3 = "CS";
    table.update(columns, values, s2, s3);
    vector<vector<string>> t2 = table.getTable();
    out.showTable(t2);
    return 0;
}
