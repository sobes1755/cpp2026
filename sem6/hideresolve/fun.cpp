#include <print>

class A {
public:
    void f(int i)
    {
        std::println("{}: i = {}", __PRETTY_FUNCTION__, i);
    }
};


class B : public A {
public:
    void f(double d)
    {
        std::println("{}: d = {}", __PRETTY_FUNCTION__, d);
    }
};

class C : public A {
public:
    using A::f;
    void f(double d)
    {
        std::println("{}: d = {}", __PRETTY_FUNCTION__, d);
    }
};

int
main()
{

    B b;
    C c;

    b.f(10);
    b.f(5.5);
    c.f(10);
    c.f(5.5);

    B* pb = &b;
    C* pc = &c;

    pb->f(10);
    pb->f(5.5);
    pc->f(10);
    pc->f(5.5);

    A* pab = &b;
    A* pac = &c;

    pab->f(10);
    pab->f(5.5);
    pac->f(10);
    pac->f(5.5);

}
