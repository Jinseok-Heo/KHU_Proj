/*
Created by 허진석
LU Decomposition
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "nm.hpp"

using namespace std;

int main() {
    int n;
    cout << "Input matrix size: ";
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n));
    cout << "Input A matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    InversePM ipm(3, a, 13);
    /* LU
    int n;
    cout << "Input matrix size: ";
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n));
    vector<double> b(n), x(n);
    cout << "Input A matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    cout << "Input b matrix:\n";
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    LU lu(n, a);
    x = lu.LU_backward(lu.LU_forward(b));
    lu.showMatrix();

    cout << "\nMatrix x\n";
    for(int i = 0; i < n; i++) {
        cout << x[i] << " ";
        cout << '\n';
    }
    */
    return 0;
}