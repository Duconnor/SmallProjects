#ifndef CALCULATOR_STRING_VEC_MAP
#define CALCULATOR_STRING_VEC_MAP

#include <string>
#include <vector>
#include <map>
#include <stack>

using std::string;
using std::vector;
using std::map;
using std::stack;

#endif

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include "complex.h"

class Calculator {
private:
    string expression;
    vector<string> log;
    map<string, Complex> table;

    bool isOperator(char c);

    string toPostfix();
    Complex calculatePostfix();

    bool isRealNumber(int indexOfI); // is the number before i a real number

    string generateNext(string &present);

public:
    Calculator() = default;
    Calculator(string &input);

    bool isEmpty(); // is this expression empty?
    bool isBeginValid();
    bool isEndValid();
    bool isOperatorValid();
    bool isNumberValid();
    bool isIValid(); // not check whether the bracket before 'i' is a real number
    bool isLeftBracketValid();
    bool isRightBracketValid();
    bool checkError();
    bool checkBracket();

    vector<string> getErrorLog();
    string getExpression() {return expression;};

    /* the goal of preprocess is to convert number into string and test the legality of bracket before i */
    bool preprocess();
    Complex calculate();

    vector<Complex> findRoots(Complex a, Complex b, Complex c);
    Complex toComplex(string s);
    vector<Complex> solveEquation();

};

#endif
