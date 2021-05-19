#include "nm.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

#define EPS 1e-9
#define MAXITER 10

double find_absMax(std::vector<double>& a) {
    double pmax, nmax;
    pmax = *std::max_element(a.begin(), a.end());
    nmax = *std::min_element(a.begin(), a.end());
    return abs(pmax) > abs(nmax) ? pmax : nmax;
}

double find_absMin(std::vector<double>& a) {
    double pmax, nmax;
    pmax = *std::max_element(a.begin(), a.end());
    nmax = *std::min_element(a.begin(), a.end());
    return abs(pmax) < abs(nmax) ? pmax : nmax;
}

double PRError(double cur, double last) {
    return (cur - last) / cur;
}

InversePM::InversePM(int n, std::vector<std::vector<double>>& A,
                         double _alpha, double _tolerance) {
    size_of_mat = n;
    alpha = _alpha;
    tolerance = _tolerance;
    eigenvalue = -1000000;
    int k;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n);
    for(int i = 0; i < n; i++) {
        A[i][i] -= alpha;
    }
    LU lu(n, A);

    for(k = 0; k < MAXITER; k++) {
        std::vector<double> z = lu.LU_forward(x);
        y = lu.LU_backward(z);
        for(int i = 0; i < n; i++) {
            std::cout << y[i] << " ";
        }
        std::cout << '\n';
        double r = find_absMax(y);
        for(int i = 0; i < n; i++) {
            x[i] = y[i] / r;
        }
        if(abs(PRError(r, eigenvalue)) < tolerance) {
            eigenvalue = r;
            eigenvector = x;
            break;
        }
        eigenvalue = r;
        eigenvector = x;
    }
    //eigenvalue = 1 / eigenvalue;
    //eigenvalue += alpha;
    if(k != MAXITER)
        showMatrix();
    else
        std::cout << "Need higer number of iterate\n";
}

void InversePM::showMatrix() {
    std::cout << "Eigenvalue: " << eigenvalue << '\n';
    std::cout << "Eigenvector:\n";
    for(int i = 0; i < size_of_mat; i++) {
        std::cout << eigenvector[i] << " ";
    }
    std::cout << '\n';
}

PowerMethod::PowerMethod(int n, std::vector<std::vector<double>>& A,
                         double _alpha, double _tolerance) {
    size_of_mat = n;
    alpha = _alpha;
    tolerance = _tolerance;
    eigenvalue = -1000000;
    int k;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n);
    for(int i = 0; i < n; i++) {
        A[i][i] -= alpha;
    }

    for(k = 0; k < MAXITER; k++) {
        for(int i = 0; i < n; i++) {
            double sum = 0;
            for(int j = 0; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            y[i] = sum;
        }
        double r = find_absMax(y);
        for(int i = 0; i < n; i++) {
            x[i] = y[i] / r;
        }
        if(abs(PRError(r, eigenvalue)) < tolerance) {
            eigenvalue = r;
            eigenvector = x;
            break;
        }
        eigenvalue = r;
        eigenvector = x;
    }
    eigenvalue += alpha;
    if(k != MAXITER)
        showMatrix();
    else
        std::cout << "Need higer number of iterate\n";
}

void PowerMethod::showMatrix() {
    std::cout << "Eigenvalue: " << eigenvalue << '\n';
    std::cout << "Eigenvector:\n";
    for(int i = 0; i < size_of_mat; i++) {
        std::cout << eigenvector[i] << " ";
    }
    std::cout << '\n';
}

LU::LU(int n, std::vector<std::vector<double>>& A) {
    size_of_mat = n;
    L_mat.resize(size_of_mat, std::vector<double>(size_of_mat, 0));
    U_mat.resize(size_of_mat, std::vector<double>(size_of_mat, 0));
    cholesky.resize(size_of_mat, std::vector<double>(size_of_mat, 0));
    for(int i = 0; i < size_of_mat; i++)
        U_mat[i][i] = 1;

    LU_process(A);
    Cholesky_process(A);
}

void LU::LU_process(std::vector<std::vector<double>>& A) {
    for (int k = 0; k < size_of_mat; k++) {
        for (int i = k; i < size_of_mat; i++) {
            double sum = 0;
            for (int j = 0; j < k; j++) {
                sum += L_mat[i][j] * U_mat[j][k];
            }
            L_mat[i][k] = A[i][k] - sum;
        }
        for (int i = k + 1; i < size_of_mat; i++) {
            double sum = 0;
            for (int j = 0; j < k; j++) {
                sum += L_mat[k][j] * U_mat[j][i];
            }
            U_mat[k][i] = (A[k][i] - sum) / L_mat[k][k];
        }
    }
}
void LU::Cholesky_process(std::vector<std::vector<double>>& A) {
    for(int k = 0; k < size_of_mat; k++) {
        double sum = 0;
        for(int i = 0; i < k; i++) {
            sum += cholesky[k][i] * cholesky[k][i];
        }
        cholesky[k][k] = sqrt(A[k][k] - sum);
        for(int i = k + 1; i < size_of_mat; i++) {
            sum = 0;
            for(int j = 0; j < k; j++) {
                sum += cholesky[i][j] * cholesky[k][j];
            }
            cholesky[i][k] = (A[i][k] - sum) / cholesky[k][k];
        }
    }
}

std::vector<double> LU::LU_forward(std::vector<double>& b) {
    std::vector<double> Z_mat(size_of_mat);
    for(int k = 0; k < size_of_mat; k++) {
        long double sum = 0;
        for (int j = 0; j < k; j++) {
            sum += (long double)L_mat[k][j] * Z_mat[k];
        }
        Z_mat[k] = (b[k] - sum) / L_mat[k][k];
    }
    return Z_mat;
}

std::vector<double> LU::LU_backward(std::vector<double>& Z) {
    std::vector<double> X_mat(size_of_mat);
    for(int k = size_of_mat - 1; k >= 0; k--) {
        long double sum = 0;
        for(int j = size_of_mat - 1; j > k; j--) {
            sum += (long double)U_mat[k][j] * X_mat[j];
        }
        X_mat[k] = (Z[k] - sum) / U_mat[k][k];
    }
    return X_mat;
}

void LU::showMatrix() {
    std::cout << "Matrix L\n";
    for(int i = 0; i < size_of_mat; i++) {
        for(int j = 0; j < size_of_mat; j++) {
            std::cout << std::setw(8) << std::setprecision(3) << std::fixed << L_mat[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\nMatrix U\n";
    for(int i = 0; i < size_of_mat; i++) {
        for(int j = 0; j < size_of_mat; j++) {
            std::cout << std::setw(8) << std::setprecision(3) << std::fixed << U_mat[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\nMatrix Cholesky\n";
    for(int i = 0; i < size_of_mat; i++) {
        for(int j = 0; j < size_of_mat; j++) {
            std::cout << std::setw(8) << std::setprecision(3) << std::fixed << cholesky[i][j] << " ";
        }
        std::cout << '\n';
    }
}

LSE::LSE(int maxOrder, std::vector<double>& x_val, std::vector<double>& y_val) {
    int n = x_val.size();
    ord = maxOrder;
    std::vector<std::vector<double>> resMat(ord + 1, std::vector<double>(ord + 1, 0));
    if(x_val.size() != y_val.size()) {
        std::cout << "Size of input value is not correct!\n";
        return;
    }
    for(int i = 0; i <= ord * 2; i++) {
        double sum = 0.0;
        for(int j = 0; j < n; j++) {
            sum += pow(x_val[j], i);
        }
        if(i <= ord) {
            for(int j = 0; j <= i; j++) {
                resMat[j][i - j] = sum;
            }
        }
        else {
            for(int j = i - ord; j <= ord; j++) {
                resMat[j][i - j] = sum;
            }
        }
    }
    A_mat = resMat;
    Y_mat.resize(ord + 1);
    for(int i = 0; i <= ord; i++) {
        double sum = 0.0;
        for(int j = 0; j < n; j++) {
            sum += y_val[j] * pow(x_val[j], i);
        }
        Y_mat[i] = sum;
    }
}

std::vector<double> LSE::findCoef() {
    LU lu(ord + 1, A_mat);
    std::vector<double> Z = lu.LU_forward(Y_mat);
    coef_mat = lu.LU_backward(Z);
    lu.showMatrix();
    return coef_mat;
}

void LSE::showMatrix() {
    std::cout << "\nMatrix A\n";
    for(int i = 0; i < ord + 1; i++) {
        for(int j = 0; j < ord + 1; j++) {
            std::cout << std::setw(15) << std::setprecision(3) << std::fixed << A_mat[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\nMatrix Coef\n";
    for(int i = 0; i < ord + 1; i++) {
        std::cout << std::setw(15) << std::setprecision(3) << std::fixed << coef_mat[i] << " ";
    }

    std::cout << "\n\nMatrix Y\n";
    for(int i = 0; i < ord + 1; i++) {
        std::cout << std::setw(15) << std::setprecision(3) << std::fixed << Y_mat[i] << " ";
    }
    std::cout << '\n';
}