#include <iostream>

class D {
public:
    int y = 40;
};

class E : public D {
public:
    int y = 50;
};

class F : public E {
public:
    int y = 60;
};

int
main()
{

    F obj;

    std::cout << "F::x = " << obj.y << std::endl;
    std::cout << "E::x = " << obj.E::y << std::endl;
    std::cout << "D::x = " << obj.D::y << std::endl;

}
