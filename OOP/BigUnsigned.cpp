#include "BigUnsigned.h"
#define D '0' - 0

int addDecimal(int x, int y, int& over_ten) {
    // Digit of x and y should be 1
    int add = x + y + over_ten;
    if (add > 9) {
        over_ten = add / 10;
        add -= over_ten * 10;
    }
    else {
        over_ten = 0;
    }
    return add;
}

BigUnsigned::BigUnsigned() {
    num_container.push_back(0);
}

BigUnsigned::BigUnsigned(unsigned long long num) {
    while(num) {
        num_container.push_back(num % 10);
        num /= 10;
    }
    std::reverse(num_container.begin(), num_container.end());
}

BigUnsigned::BigUnsigned(BigUnsigned& num) {
    num_container = num.get_vector();
}

BigUnsigned::BigUnsigned(std::string& num) {
    for(int i = 0; i < num.size(); i++) {
        if (num[i] < '0' || num[i] > '9') {
            std::cout << "Wrong Value!\n";
        }
        num_container.push_back(int(num[i]) - D);
    }
}

std::vector<int> BigUnsigned::get_vector() {
    return num_container;
}

unsigned long long BigUnsigned::to_integer() {
    unsigned long long ull = 0;
    int n = num_container.size();
    for (int i = 0; i < n; i++) {
        ull += num_container[i] * (unsigned long long)pow(10, n - i - 1);
    }
    return ull;
}

std::ostream& operator<<(std::ostream& os, BigUnsigned num) {
    std::vector<int> n = num.get_vector();
    for (int i = 0; i < n.size(); i++) {
        os << n[i];
    }
    return os;
}

const BigUnsigned operator+(BigUnsigned& num1, BigUnsigned& num2) {
    std::string new_container;
    std::vector<int> first_container = num1.get_vector();
    std::vector<int> second_container = num2.get_vector();
    std::reverse(first_container.begin(), first_container.end());
    std::reverse(second_container.begin(), second_container.end());
    int over_ten = 0, i;
    for (i = 0; i < first_container.size() && i < second_container.size(); i++) {
        int add = addDecimal(first_container[i], second_container[i], over_ten);
        new_container.push_back(add + D);
    }
    if (i != first_container.size()) {
        while (i < first_container.size()) {
            int add = addDecimal(first_container[i++], over_ten, over_ten);
            new_container.push_back(add + D);
        }
    }
    else if (i != second_container.size()) {
        while (i < second_container.size()) {
            int add = addDecimal(second_container[i++], over_ten, over_ten);
            new_container.push_back(add + D);
        }
    }
    std::reverse(new_container.begin(), new_container.end());
    BigUnsigned ret(new_container);
    return ret;
}