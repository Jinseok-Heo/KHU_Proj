/*
Created by 허진석
Difference Table
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "nm.hpp"

void show_Dtable(std::vector<std::vector<double>>& Dtable) {
    int n = Dtable.size();
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < Dtable[i].size(); j++) {
            std::cout << std::setw(14) << std::setprecision(9) << std::fixed << Dtable[i][j];
        }
        std::cout << '\n';
    }
}

void difference_table(std::vector<double>& x_val, std::vector<double>& y_val) {
    int n = x_val.size();
    std::vector<std::vector<double>> Dtable(n);
    Dtable[0] = y_val;
    for (int i = 1; i < n; i++) {
        Dtable[i].resize(n - i);
        for (int j = 0; j < n - i; j++) {
            Dtable[i][j] = (Dtable[i - 1][j + 1] - Dtable[i - 1][j]);
        }
    }
    show_Dtable(Dtable);
}

int main() {
    int n;
    std::cout << "Input size of Table: ";
    std::cin >> n;

    std::vector<double> x_val(n);
    std::vector<double> y_val(n);

    std::cout << "Input X Values\n";
    for(int i = 0; i < n; i++) 
        std::cin >> x_val[i];
    
    std::cout << "Input Y Values\n";
    for(int i = 0; i < n; i++) 
        std::cin >> y_val[i];

    difference_table(x_val, y_val);
    return 0;
}