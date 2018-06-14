#define TEST 0
#if TEST == 1
#include "console.h"

// unit test for class Complex
/*
int main() {
    double real, imag;
    while (std::cin >> real >> imag) {
        Complex myComplex(real, imag);
        std::cout << myComplex.toString() << std::endl;
        std::cin >> real >> imag;
        Complex another(real, imag);
        std::cout << another.toString() << std::endl;
        Complex sum = another + myComplex;
        std::cout << sum.toString() << std::endl;
        Complex diff = another - myComplex;
        std::cout << diff.toString() << std::endl;
        Complex prod = another * myComplex;
        std::cout << prod.toString() << std::endl;
        Complex quo = another / myComplex;
        std::cout << quo.toString() << std::endl;
        std::cout << sum.argument() << std::endl;
        std::cout << (sum.power(-1)).toString() << std::endl;
    }
    return 0;
}
*/

// unit test for class Calculator

/*
int main() {
    string s;
    while (std::getline(std::cin, s)) {
        Calculator calculator(s);
        calculator.checkError();
        vector<string> log = calculator.getErrorLog();
        std::cout << calculator.getExpression() << std::endl;
        for (auto s: log)
            std::cout << s << std::endl;
        Complex res = calculator.calculate();
        std::cout << res.toString() << std::endl;
    }
    return 0;
}
*/

// unit test for class Console


int main() {
  Console console;
  console.start();
}
#endif
