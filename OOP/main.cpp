#include <iostream>
#include "BigUnsigned.h"

int main() {
    std::string s = "2521356";
    BigUnsigned a(1234);
    BigUnsigned b(2595678);
    BigUnsigned c(s);
    std::cout << "Big Unsigned\n";
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
    std::cout << "a + b: " << a + b << '\n';
    std::cout << "c: " << c << '\n';
    std::cout << "c(integer): " << c.to_integer() << '\n';
    return 0;
}