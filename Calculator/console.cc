#include "console.h"
#include <string.h>
#include <iostream>

#define UP "\033[A"
#define DOWN "\033[B"

vector<string> Console::splitBy(char delim, string &s) {
    vector<string> result;
    int length = s.length();
    int start = 0;
    for (int i = 0; i < length; i++) {
        if (s[i] == delim) {
            string part = s.substr(start, i - start);
            result.push_back(part);
            start = i + 1;
        }
    }
    if (start != length - 1) {
        string part = s.substr(start, length - start);
        result.push_back(part);
    }
    return result;
}

string Console::getExpression() {
    string expression;
    std::getline(std::cin, expression);
    expressionVector.push_back(expression);
    return expression;
}

void Console::calculate(string &expression) {
    Calculator calculator(expression);
    Complex result = calculator.calculate();
    vector<string> log = calculator.getErrorLog();
    if (log.size() == 0)
        std::cout << "The result is: " << result.toString() << std::endl;
    else {
        for (auto s: log) {
            vector<string> splitRes = splitBy(',', s);
            vector<int> indexVec;
            string errorInfo;
            for (auto element: splitRes) {
                bool isNumber = true;
                for (auto c: element) {
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }
                if (isNumber) {
                    int index = atoi(element.c_str());
                    indexVec.push_back(index);
                } else
                    errorInfo = element;
            }
            int indexNow = 0;
            for (int i = 0; i < expression.size(); i++) {
                if (i == indexVec[indexNow]) {
                    indexNow++;
                    std::cout << "\033[31;4m" << expression[i] << "\e[0m";
                } else
                    std::cout << expression[i];
            }
            std::cout << " " << errorInfo << std::endl;
        }
    }
}

bool Console::getPreviousExpression() {
    int length = expressionVector.size();
    for (int i = 0; i < length; i++) {
        if (expressionVector[i] == presentExpression) {
            if (i == 0)
                return false;
            else {
                presentExpression = expressionVector[i - 1];
                return true;
            }
        }
    }
    return false;
}

bool Console::getNextExpression() {
    int length = expressionVector.size();
    for (int i = 0; i < length; i++) {
        if (expressionVector[i] == presentExpression) {
            if (i == length - 1)
                return false;
            else {
                presentExpression = expressionVector[i + 1];
                return true;
            }
        }
    }
    return false;
}

vector<string> Console::recentFive() {
    int count = 0;
    vector<string> result;
    for (auto ite = expressionVector.rbegin(); ite != expressionVector.rend(); ite++) {
        result.push_back(*ite);
        count++;
        if (count == 5)
            break;
    }
    return result;
}

void Console::start() {
    string s = getExpression();
    while (s != "quit") {
        if (!strcmp(s.c_str(), UP)) {
            expressionVector.pop_back();
            if (expressionVector.size() == 0)
                std::cout << "Already the first one" << std::endl;
            else {
                if (getPreviousExpression())
                    std::cout << presentExpression << std::endl;
                else
                    std::cout << "Already the first one" << std::endl;
            }
            s = getExpression();
            continue;
        } else if (!strcmp(s.c_str(), DOWN)) {
            expressionVector.pop_back();
            if (expressionVector.size() == 0)
                std::cout << "Already the last one" << std::endl;
            else {
                if (getNextExpression())
                    std::cout << presentExpression << std::endl;
                else
                    std::cout << "Already the last one" << std::endl;
            }
            s = getExpression();
            continue;
        } else if (s == "recent five") {
            expressionVector.pop_back();
            vector<string> res = recentFive();
            for (auto str: res)
                std::cout << str << std::endl;
            s = getExpression();
            continue;
        }
        presentExpression = s;
        calculate(s);
        s = getExpression();
    }
}
