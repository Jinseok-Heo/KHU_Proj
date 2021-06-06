#include <iostream>
#include <vector>

class Base {
protected:
    std::vector<int> container;
public:
    Base(const int& s) {
        container.resize(s, 0);
    }
    void setN(const int& idx, const int& val) {
        if (idx < container.size()) {
            container[idx] = val;
        }
    }
    void print() {
        std::cout << container.size() << '\n';
    }
    void printData() {
        for (int ele: container)
            std::cout << ele << " ";
        std::cout << '\n';
    }
};

class Derived: public Base {
public:
    Derived(const int& s)
        : Base(s) {}

    void insert(const int& x) {
        container.push_back(x);
    }
};

int main() {
    Base b1(2), b2(10);

    b1.print(); // 1
    b2.print(); // 10
    for (int i = 0; i < 5; i++) {
        b1.setN(i, (i + 1) * 20);
        b2.setN(i, (i + 1) * 10);
    }
    b1.printData(); // 20 40
    b2.printData(); // 10 20 30 40 50 0 0 0 0 0

    Derived d(5);
    d.print();     // 5
    d.printData(); // 0 0 0 0 0
    for (int i = 0; i < 10; i++) {
        d.setN(i, (i + 1) * 3);
    }
    d.printData(); // 3 6 9 12 15
    d.insert(99);  // "Base" class does not have "insert" method.
    d.printData(); // 3 6 9 12 15 99
}