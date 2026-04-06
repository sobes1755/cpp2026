#include <print>

class A {
public:
    virtual void g(int i = 1)
    {
        std::println("{}: i = {}", __PRETTY_FUNCTION__, i);
    }
};


class B : public A {
public:
    void g(int i = 2) override
    {
        std::println("{}: i = {}", __PRETTY_FUNCTION__, i);
    }
};

int
main()
{

    A a;
    B b;

    a.g();
    b.g();

    A* paa = &a;
    A* pab = &b;
    // B* pba = &a;
    B* pbb = &b;

    paa->g();
    pab->g();
    // pba->g();
    pbb->g();

}
