#include <iostream>

class A {
protected:
    int x = 10;
};

class B : public A {
protected:
    int x = 20;
};

class C : public B {
protected:
    int x = 30;

public:
    void print() {
        std::cout << "C::x = " << x << std::endl;
        std::cout << "B::x = " << B::x << std::endl;
        std::cout << "A::x = " << A::x << std::endl;
    }
};

int
main()
{

    C obj;
    obj.print();

}
