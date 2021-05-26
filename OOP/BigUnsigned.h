#ifndef _BIG_UNSIGNED_
#define _BIG_UNSIGNED_
#include <vector>
#include <string>
#include <iostream>

class BigUnsigned {
private:
    std::vector<int> num_container;
public:
    BigUnsigned();
    BigUnsigned(unsigned long long num);
    BigUnsigned(BigUnsigned& num);
    BigUnsigned(std::string& num);

    std::vector<int> get_vector();
    unsigned long long to_integer();
    friend std::ostream& operator<<(std::ostream& os, BigUnsigned num);
    friend const BigUnsigned operator+(BigUnsigned& num1, BigUnsigned& num2);
};
#endif