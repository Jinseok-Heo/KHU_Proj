/*
Created by 허진석
LU Decomposition
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "nm.hpp"

int main() {
    // int n;
    // std::cout << "Input size of Table: ";
    // std::cin >> n;

    // std::vector<double> x_val(n);
    // std::vector<double> y_val(n);

    // std::cout << "Input X Values\n";
    // for(int i = 0; i < n; i++) 
    //     std::cin >> x_val[i];
    
    // std::cout << "Input Y Values\n";
    // for(int i = 0; i < n; i++) 
    //     std::cin >> y_val[i];

    // LSE lse(2, x_val, y_val);
    // std::vector<double> coef = lse.findCoef();
    // lse.showMatrix();
    int n;
    std::cin >> n;
    std::vector<std::vector<double>> x_val(n, std::vector<double>(n, 0));
    std::vector<double> y_val(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> x_val[i][j];

    for (int i = 0; i < n; i++)
        std::cin >> y_val[i];

    LU lu(n, x_val);
    std::vector<double> z = lu.LU_forward(y_val);
    std::vector<double> sol = lu.LU_backward(z);

    for(int i = 0; i < sol.size(); i++) {
        std::cout << sol[i] << " ";
    }

    return 0;
}