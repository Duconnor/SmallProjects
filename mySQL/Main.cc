#include "process.h"

int main() {
    string s = "fileTable.txt";
    string s1 = "tableName.txt";
    while (true) {
        Input in;
        string control = in.getString();
        if (control != "mySQL")
            continue;
        Process process(s, s1);
        process.applicationOn();
    }
    return 0;
}
