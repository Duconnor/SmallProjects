#include "calculator.h"
#include <cctype>
#include <stdlib.h>

bool Calculator::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string Calculator::toPostfix() {
    // assuming the expression is a legal infix expression -> || was replaced by 'm' and () and arg was replaced by a and cjg becomes c
    // shutting-yard algorithm
    stack<char> operatorStack;
    string result;
    int length = expression.length();
    for (int i = 0; i < length; i++) {
        if (isalpha(expression[i]) && isupper(expression[i])) {
            // encounter operand
            for (int j = 0; j < 4; j++)
                result.push_back(expression[i + j]);
            i += 3;
        } else {
            // encounter operator
            char thisOperator = expression[i];
            if (thisOperator == '(')
                operatorStack.push(thisOperator);
            else if (thisOperator == ')') {
                while (!operatorStack.empty()) {
                    char newOperator = operatorStack.top();
                    if (newOperator == '(') {
                        operatorStack.pop();
                        break;
                    }
                    result.push_back(newOperator);
                    operatorStack.pop();
                }
            } else if (thisOperator == 'm' || thisOperator == 'c' || thisOperator == 'a'){
                while (!operatorStack.empty()) {
                    char newOperator = operatorStack.top();
                    if (newOperator == 'm' || newOperator == 'a' || newOperator == 'c') {
                        result.push_back(newOperator);
                        operatorStack.pop();
                    } else
                        break;
                }
                operatorStack.push(thisOperator);
            } else if (thisOperator == '^') {
                while (!operatorStack.empty()) {
                    char newOperator = operatorStack.top();
                    if (newOperator == 'm' || newOperator == 'c' || newOperator == 'a' || newOperator == '^') {
                        result.push_back(newOperator);
                        operatorStack.pop();
                    } else
                        break;
                }
                operatorStack.push(thisOperator);
            } else if (thisOperator == '*' || thisOperator == '/') {
                while (!operatorStack.empty()) {
                    char newOperator = operatorStack.top();
                    if (newOperator == 'm' || newOperator == 'c' || newOperator == 'a' || newOperator == '^' ||
                            newOperator == '*' || newOperator == '/') {
                        result.push_back(newOperator);
                        operatorStack.pop();
                    } else
                        break;
                }
                operatorStack.push(thisOperator);
            } else if (thisOperator == '+' || thisOperator == '-') {
                while (!operatorStack.empty()) {
                    char newOperator = operatorStack.top();
                    if (newOperator == 'm' || newOperator == 'c' || newOperator == 'a' || newOperator == '^' ||
                            newOperator == '*' || newOperator == '/' || newOperator == '+' || newOperator == '-') {
                        result.push_back(newOperator);
                        operatorStack.pop();
                    } else
                        break;
                }
                operatorStack.push(thisOperator);
            }
        }
    }
    while (!operatorStack.empty()) {
        char newOperator = operatorStack.top();
        result.push_back(newOperator);
        operatorStack.pop();
    }
    return result;
}

Complex Calculator::calculatePostfix() {
    // assuming the expression has already been transformed into postfix form
    stack<Complex> complexStack;
    int length = expression.length();
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (isalpha(present) && isupper(present)) {
            if (i + 3 >= length)
                continue;
            string s = expression.substr(i, 4);
            i += 3;
            Complex temp = table[s];
            complexStack.push(temp);
        } else {
            if (present == 'a' || present == 'c' || present == 'm') {
                Complex operand;
                if (!complexStack.empty()) {
                    operand = complexStack.top();
                    complexStack.pop();
                }
                if (present == 'a')
                    operand = operand.argument();
                else if (present == 'c')
                    operand = operand.conjugate();
                else
                    operand = operand.modulo();
                complexStack.push(operand);
            } else {
                Complex operandLeft, operandRight;
                if (!complexStack.empty()) {
                    operandRight = complexStack.top();
                    complexStack.pop();
                }
                if (!complexStack.empty()) {
                    operandLeft = complexStack.top();
                    complexStack.pop();
                }
                Complex result;
                if (present == '^')
                    result = operandLeft.power(operandRight);
                else if (present == '*')
                    result = operandLeft * operandRight;
                else if (present == '/')
                    result = operandLeft / operandRight;
                else if (present == '+')
                    result = operandLeft + operandRight;
                else if (present == '-')
                    result = operandLeft - operandRight;
                complexStack.push(result);
            }
        }
    }
    Complex finalResult;
    if (!complexStack.empty())
        finalResult = complexStack.top();
    return finalResult;
}

bool Calculator::isRealNumber(int indexOfI) {
    int i = indexOfI - 1;
    if (i == -1)
        return true;
    char c = expression[i];
    if (isdigit(c))
        return true;
    else if (c == 'i')
        return false;
    else if (c == ')') {
        stack<char> auxStack;
        auxStack.push(c);
        int start = -1, end = i;
        i--;
        while(!auxStack.empty() && i >= 0) {
            c = expression[i];
            if (c == '(')
                auxStack.pop();
            i--;
        }
        start = i + 1;
        if (start - 3 >= 0 && expression[start - 3] == 'a')
            return true;
        string num = expression.substr(start, end - start + 1);
        Calculator temp(num);
        Complex res = temp.calculate();
        if (res.isReal())
            return true;
        else
            return false;
    } else
        return true;
}

string Calculator::generateNext(string &present) {
    string result(present);
    char four = present[3], three = present[2], two = present[1], one = present[0];
    if (four != 'Z') {
        result.pop_back();
        four = four + 1;
        result.push_back(four);
    } else if (three != 'Z') {
        result.pop_back();
        result.pop_back();
        three = three + 1;
        result.push_back(three);
        result.push_back('A');
    } else if (two != 'Z') {
        result.pop_back();
        result.pop_back();
        result.pop_back();
        two = two + 1;
        result.push_back(two);
        result.push_back('A');
        result.push_back('A');
    } else if (one != 'Z') {
        one = one + 1;
        result[0] = one;
        result[1] = result[2] = result[3] = 'A';
    }
    return result;
}

Calculator::Calculator(string &input) {
    int length = input.length();
    int i = 0;
    expression = input;
    while (i < length) {
        if (expression[i] == ' ') {
            expression.erase(expression.begin() + i);
            length--;
        } else
            i++;
    }
}

bool Calculator::isEmpty() {
    if (expression.length() == 0) {
        string errorLog = "-1,Empty expression";
        log.push_back(errorLog);
        return false;
    }
    return true;
}

bool Calculator::isBeginValid() {
    char begin = expression[0];
    if (isdigit(begin) || begin == '|' || begin == '-' || begin == 'i' || begin == '(')
        return true;
    else if (begin == 'a' || begin == 'c') {
        if (expression.length() < 3) {
            string errorLog = "-1,Incomplete expression";
            log.push_back(errorLog);
            return false;
        }
        char second = expression[1], third = expression[2];
        if (begin == 'a' && second == 'r' && third == 'g')
            return true;
        if (begin == 'c' && second == 'j' && third == 'g')
            return true;
        string errorLog = "0,1,2,Invalid start";
        log.push_back(errorLog);
        return false;
    }
}

bool Calculator::isEndValid() {
    int length = expression.length();
    char end = expression[length - 1];
    if (isdigit(end) || end == 'i' || end == '|' || end == ')')
        return true;
    else {
        string errorLog = std::to_string(length - 1) + ",Invalid end";
        log.push_back(errorLog);
        return false;
    }
}

bool Calculator::isOperatorValid() {
    bool flag = true;
    for (int i = 0; i < expression.length(); i++) {
        char present = expression[i];
        if (present == '+' || present == '-' || present == '*' || present == '/') {
            if (i + 1 == expression.length()) {
                // this is the last one
                string errorLog = std::to_string(i) + ",Invalid operator";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
            char behindOperator = expression[i + 1];
            if (isdigit(behindOperator) || behindOperator == 'i' || behindOperator == '|' || behindOperator == '(')
                continue;
            if (behindOperator == 'a' || behindOperator == 'c') {
                if (i + 3 >= expression.length()) {
                    string errorLog = std::to_string(i) + ",Invalid operator";
                    log.push_back(errorLog);
                    flag = false;
                    continue;
                } else {
                    char second = expression[i + 2], third = expression[i + 3];
                    if (behindOperator == 'a' && second == 'r' && third == 'g')
                        continue;
                    else if (behindOperator == 'c' && second == 'j' && third == 'g')
                        continue;
                    else {
                        string errorLog = std::to_string(i) + ",Invalid operator";
                        log.push_back(errorLog);
                        flag = false;
                        continue;
                    }
                }
            }
            string errorLog = std::to_string(i) + "," + std::to_string(i + 1) + ",Operator mismatch";
            log.push_back(errorLog);
            flag = false;
            continue;
        }
    }
    return flag;
}

bool Calculator::isNumberValid() {
    int length = expression.length();
    bool evenMod = true, flag = true;
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (present == '|')
            evenMod = evenMod ^ 1;
        if (isdigit(present)) {
            if (i + 1 >= length)
                continue;
            char behindNumber = expression[i + 1];
            if (behindNumber == ')' || behindNumber == 'i' || isOperator(behindNumber)
                    || behindNumber == '^' || isdigit(behindNumber) || behindNumber == '.')
                continue;
            if (behindNumber == '|' && !evenMod)
                continue;
            string errorLog = std::to_string(i) + "," + std::to_string(i + 1) + ",Number mismatch";
            log.push_back(errorLog);
            flag = false;
        }
    }
    return flag;
}

bool Calculator::isIValid() {
    int length = expression.length();
    bool flag = true, evenMod = true;
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (present == '|')
            evenMod = evenMod ^ 1;
        if (present == 'i') {
            // check before first
            if (i != 0) {
                char before = expression[i - 1];
                if (!(before == '|' || isOperator(before) || isdigit(before) || before == ')' || before == '(')) {
                    string errorLog = std::to_string(i - 1) + "," + std::to_string(i) + ",i mismatch";
                    log.push_back(errorLog);
                    flag = false;
                }
            }

            // check after
            if(i != length - 1) {
                char after = expression[i + 1];
                if (after == ')' || isOperator(after))
                    continue;
                if (after == '|' && !evenMod)
                    continue;
                string errorLog = std::to_string(i) + "," + std::to_string(i + 1) + ",i mismatch";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
        }
    }
    return flag;
}

bool Calculator::isLeftBracketValid() {
    int length = expression.length();
    bool flag = true;
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (present == '(') {
            if (i == length - 1) {
                string errorLog = std::to_string(i) + ",Invalid left bracket end";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
            char after = expression[i + 1];
            if (after == '(' || isdigit(after) || after == 'i' || after == '|' || after == '-')
                continue;
            if (after == 'a' || after == 'c') {
                if (i + 3 >= length) {
                    string errorLog = std::to_string(i) + ",Invalid left bracket";
                    log.push_back(errorLog);
                    flag = false;
                    continue;
                }
                char second = expression[i + 2], third = expression[i + 3];
                if (after == 'a' && second == 'r' && third == 'g')
                    continue;
                else if (after == 'c' && second == 'j' && third == 'g')
                    continue;
                else {
                    string errorLog = std::to_string(i) + ",Invalid left bracket";
                    log.push_back(errorLog);
                    flag = false;
                    continue;
                }
            }
            string errorLog = std::to_string(i) + "," + std::to_string(i + 1) + ",Left bracket mismatch";
            log.push_back(errorLog);
            flag = false;
        }
    }
    return flag;
}

bool Calculator::isRightBracketValid() {
    int length = expression.length();
    bool flag = true;
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (present == ')') {
            if (i == 0) {
                string errorLog = "0,Invalid right bracket at start";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
            if (i == length - 1)
                continue;
            char after = expression[i + 1];
            if (after == ')' || after == 'i' || after == '^' || isOperator(after))
                continue;
            else {
                string errorLog = std::to_string(i) + "," + std::to_string(i + 1) + ",Right bracket mismatch";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
        }
    }
    return flag;
}

bool Calculator::checkError() {
    bool flag1 = isEmpty();
    bool flag2 = isBeginValid();
    bool flag3 = isEndValid();
    bool flag4 = isOperatorValid();
    bool flag5 = isNumberValid();
    bool flag6 = isIValid();
    bool flag7 = isLeftBracketValid();
    bool flag8 = isRightBracketValid();
    return flag1 && flag2 && flag3 && flag4 && flag5 && flag6 && flag7 && flag8;
}

vector<string> Calculator::getErrorLog() {
    return log;
}

bool Calculator::preprocess() {
    string result;
    bool flag = true, evenMod = true;
    int length = expression.length();
    string presentString = "AAAA";
    for (int i = 0; i < length; i++) {
        char present = expression[i];
        if (isdigit(present)) {
            int j = i + 1;
            while (j < length) {
                if (isdigit(expression[j]) || expression[j] == '.')
                    j++;
                else
                    break;
            }
            if (i - 1 == 0) {
                if (expression[i - 1] == '-')
                    i--;
            } else {
                if (expression[i - 1] == '-' && expression[i - 2] == '(')
                    i--;
            }
            string number = expression.substr(i, j - i);
            double val = atof(number.c_str());
            Complex comp(val, 0.0);
            result = result + presentString;
            table[presentString] = comp;
            presentString = generateNext(presentString);
            i = j - 1;
        } else if (present == 'i') {
            if (!isRealNumber(i)) {
                string errorLog = std::to_string(i) + ",Not a real number before i";
                log.push_back(errorLog);
                flag = false;
                continue;
            }
            // a valid expression
            Complex comp(0.0, 1);
            table[presentString] = comp;
            if (i == 0 || isOperator(expression[i - 1]))
                result = result + presentString;
            else
                result = result + "*" + presentString;
            presentString = generateNext(presentString);
        } else if (present == 'a' || present == 'c') {
            result.push_back(present);
            i = i + 2;
        } else if (present == '|') {
            if (evenMod)
                result = result + "m(";
            else
                result.push_back(')');
            evenMod = evenMod ^ 1;
        } else if (present == '-') {
            if (i == 0 || expression[i - 1] == '(')
                continue;
            else
                result.push_back(present);
        } else
            result.push_back(present);
    }
    expression = result;
    return flag;
}

Complex Calculator::calculate() {
    bool flag1 = checkError();
    bool flag2 = preprocess();
    Complex result;
    if (!flag1 || !flag2)
        return result;
    else {
        string postfix = toPostfix();
        expression = postfix;
        result = calculatePostfix();
        return result;
    }
}
