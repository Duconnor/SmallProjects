#include "complex.h"
#include <cmath>
#include <float.h>

Complex::Complex(const Complex& that) {
    realPart = that.realPart;
    imaginaryPart = that.imaginaryPart;
}

Complex& Complex::operator=(const Complex& that) {
    realPart = that.realPart;
    imaginaryPart = that.imaginaryPart;
}

string Complex::toString() {
    string real = std::to_string(realPart);

    // processing to meet the precision requirement

    // bug here: detect whether a number need to change
    auto ite = real.rbegin();
    for (; ite != real.rend(); ite++) {
        if (*ite == '0')
            real.pop_back();
        else
            break;
    }
    if (*ite == '.')
        real.pop_back();
    double temp = atof(real.c_str());
    if (temp != realPart)
        real = std::to_string(realPart);

    string imag = std::to_string(imaginaryPart);
    auto ite2 = imag.rbegin();
    for (; ite2 != imag.rend(); ite2++) {
        if (*ite2 == '0')
            imag.pop_back();
        else
            break;
    }
    if (*ite2 == '.')
        imag.pop_back();
    temp = atof(imag.c_str());
    if (temp != imaginaryPart)
        imag = std::to_string(imaginaryPart);

    string sign = "+";
    if (imag[0] == '-')
        sign.pop_back();
    string result;
    if (imaginaryPart == 0 && realPart == 0)
        result = "0";
    if (imaginaryPart == 0 && realPart != 0)
        result = real;
    if (realPart == 0 && imaginaryPart != 0) {
        if (sign == "-")
            result = sign + imag + "i";
        else
            result = imag + "i";
    }
    if (realPart != 0 && imaginaryPart != 0)
        result = real + sign + imag + "i";
    return result;
}

Complex Complex::operator+(const Complex& that) {
    Complex sum;
    sum.realPart = realPart + that.realPart;
    sum.imaginaryPart = imaginaryPart + that.imaginaryPart;
    return sum;
}

Complex Complex::operator-(const Complex& that) {
    Complex diff;
    diff.realPart = realPart - that.realPart;
    diff.imaginaryPart = imaginaryPart - that.imaginaryPart;
    return diff;
}

Complex Complex::operator*(const Complex& that) {
    Complex product;
    product.realPart = that.realPart * realPart - that.imaginaryPart * imaginaryPart;
    product.imaginaryPart = realPart * that.imaginaryPart + imaginaryPart * that.realPart;
    return product;
}

Complex Complex::operator/(const Complex& that) {
    Complex quotient;
    double denominator = that.realPart * that.realPart + that.imaginaryPart * that.imaginaryPart;
    if (denominator == 0)
        return quotient;
    quotient.realPart = (realPart * that.realPart + imaginaryPart * that.imaginaryPart) / denominator;
    quotient.imaginaryPart = (imaginaryPart * that.realPart - realPart * that.imaginaryPart) / denominator;
    return quotient;
}

Complex Complex::modulo() {
    double mod = sqrt(imaginaryPart * imaginaryPart + realPart * realPart);
    Complex res(mod, 0);
    return res;
}

Complex Complex::conjugate() {
    Complex result;
    result.realPart = realPart;
    result.imaginaryPart = -imaginaryPart;
    return result;
}

Complex Complex::argument() {
    Complex com = modulo();
    double mod = com.realPart;
    double result = asin(imaginaryPart / mod);
    Complex res(result, 0);
    return res;
}

Complex Complex::power(Complex &that) {
    Complex result;
    int n = that.realPart;
    if (n == 0) {
        if (realPart == 0 && imaginaryPart == 0) {
            result.realPart = DBL_MAX;
            result.imaginaryPart = DBL_MAX;
            return result; // error happens, 0 pow 0
        }
        result.realPart = 1;
        result.imaginaryPart = 0;
        return result;
    }
    bool positive = true;
    if (n < 0) {
        positive = false;
        n = -n;
    }
    Complex thisComplex(realPart, imaginaryPart);
    result = thisComplex;
    for (int i = 1; i < n; i++)
        result = result * thisComplex;
    if (positive)
        return result;
    else {
        Complex temp(1.0, 0.0);
        return temp / result;
    }
}

bool Complex::isReal() {
    return imaginaryPart == 0;
}
