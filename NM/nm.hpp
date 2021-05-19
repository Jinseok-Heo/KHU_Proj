#ifndef nm_hpp
#define nm_hpp

#include <vector>

class PowerMethod {
    private:
        int size_of_mat;
        double eigenvalue;
        double alpha;
        double tolerance;
        std::vector<double> eigenvector;
    public:
        PowerMethod(int n, std::vector<std::vector<double>>& A, 
                    double _alpha=0.0, double _tolerance=1e-6);
        void showMatrix();
};

class InversePM {
    private:
        int size_of_mat;
        double eigenvalue;
        double alpha;
        double tolerance;
        std::vector<double> eigenvector;
    public:
        InversePM(int n, std::vector<std::vector<double>>& A,
                  double _alpha = 0.0, double _tolerance = 1e-4);
        void showMatrix();
};

class LU {
    private:
        int size_of_mat;
        std::vector<std::vector<double>> L_mat;
        std::vector<std::vector<double>> U_mat;
        std::vector<std::vector<double>> cholesky;
    public:
        LU(int n, std::vector<std::vector<double>>& A);
        void LU_process(std::vector<std::vector<double>>& A);
        void Cholesky_process(std::vector<std::vector<double>>& A);
        std::vector<double> LU_forward(std::vector<double>& b);
        std::vector<double> LU_backward(std::vector<double>& Z);
        void showMatrix();
};

class LSE {
    private:
        int ord;
        std::vector<std::vector<double>> A_mat;
        std::vector<double> coef_mat;
        std::vector<double> Y_mat;
    public:
        LSE(int n, std::vector<double>& x_val, std::vector<double>& y_val);
        std::vector<double> findCoef();
        void showMatrix();
};

#endif /* nm_hpp */