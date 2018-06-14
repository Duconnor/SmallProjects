#ifndef CALCULATOR_STRING_VEC_MAP
#define CALCULAROR_STRING_VEC_MAP

#include <vector>

using std::vector;

#endif

#ifndef CALCULAROR_CONSOLE_H
#define CALCULATOR_CONSOLE_H

#include "calculator.h"

class Console {
private:
    vector<string> expressionVector;
    string presentExpression;

    vector<string> splitBy(char delim, string &s);

    string getExpression(); // read expression from standard input
    void calculate(string &expression); // calculate the given expression
    bool getPreviousExpression();
    bool getNextExpression();
    vector<string> recentFive();

public:
    void start();
};

#endif
