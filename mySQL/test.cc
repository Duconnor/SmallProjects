#include "process.h"

int main() {
    string s = "fileTable.txt";
    string s1 = "tableName.txt";
    Process process(s, s1);
    string s2 = "student";
    process.testProcess(s2);
    return 0;
}
