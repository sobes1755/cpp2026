#include <iostream>

class Base {
public:
    Base() { std::cout << "Base: CTR\n"; }
    ~Base() { std::cout << "Base: DTR\n"; }
};

class Derived : public Base {
private:
    double* data;
public:
    Derived() {
        std::cout << "Derived: CTR\n";
        data = new double[1024];
    }
    
    ~Derived() {
        delete[] data;
        std::cout << "Derived: DTR\n";
    }
};

int main() {

    Base* ptr = new Derived();
    delete ptr;

}
