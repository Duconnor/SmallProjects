#ifndef CALCULATOR_STRING_VEC_MAP
#define CALCULATOR_STRING_VEC_MAP

#include <string>

using std::string;

#endif


#ifndef CALCULATOR_COMPLEX_H
#define CALCULATOR_COMPLEX_H

class Complex {
private:
    double realPart;
    double imaginaryPart;

public:
    Complex():realPart(0.0), imaginaryPart(0.0) {};

    Complex(double real, double imag):realPart(real), imaginaryPart(imag) {};

    Complex(const Complex& that); // copy constructor

    ~Complex() = default;

    Complex& operator=(const Complex& that);
    string toString();

    Complex operator+(const Complex& that);
    Complex operator-(const Complex& that);
    Complex operator*(const Complex& that);
    Complex operator/(const Complex& that);

    Complex modulo();
    Complex conjugate();
    Complex argument();
    Complex power(Complex &that);
    Complex squareRoot();

    bool isReal(); // is this complex number a real number

};

#endif
