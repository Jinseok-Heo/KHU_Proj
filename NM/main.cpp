/*
Created by 허진석
Simpson's 3/8 rule
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "nm.hpp"

double func(double x) {
    return exp(x) * sin(x);
}

double integral(double a, double b, int n) {
    double h = (b - a) / n;
    std::vector<double> x(n + 1);
    for (int i = 0; i < n + 1; i++) {
        x[i] = a + h * i;
    }
    double sum = func(x[0]) + func(x[n]);
    for (int i = 1; i < n; i++) {
        if (i % 3) {
            sum += func(x[i]) * 3;
        }
        else {
            sum += func(x[i]) * 2;
        }
    }
    return sum * h * 3 / 8;
}

int main() {
    int n;
    double a, b;
    std::cout << "Input Limits of integral: ";
    std::cin >> a >> b;
    std::cout << "Input N: ";
    std::cin >> n;
    std::cout << integral(a, b, n) << '\n';

    return 0;
}