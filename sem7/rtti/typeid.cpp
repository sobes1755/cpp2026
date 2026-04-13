#include <typeinfo>
#include <string>
#include <print>

namespace S {

    struct A {
        int a_{83};
    };

    struct B : A {
        std::string b_{"S"};
    };

}

namespace D {

    struct A {
        int a_{68};
        virtual ~A() = default;
    };

    struct B : A {
        std::string b_{"D"};
    };

}

#define PRINTLN_TYPEID(x) \
    [](auto&& o, const char* s) \
    {std::println("typeid({}).name() = {}", s, typeid(o).name());}(x, #x)

int
main()
{

    {
        std::println("S::");
        S::A a;
        S::B b;
        std::println("typeid(a).name() = {}", typeid(a).name());    
        std::println("typeid(b).name() = {}", typeid(b).name());
        std::println();
    }

    {
        std::println("D::");
        D::A a;
        D::B b;
        std::println("typeid(a).name() = {}", typeid(a).name());    
        std::println("typeid(b).name() = {}", typeid(b).name());
        std::println();
    }



    {
        std::println("S::");
        S::A *paa = new S::A{};
        S::A *pab = new S::B{};
        S::B *pbb = new S::B{};
        PRINTLN_TYPEID(paa);
        PRINTLN_TYPEID(pab);
        PRINTLN_TYPEID(pbb);
        delete paa;
        delete pab;
        delete pbb;
        std::println();
    }

    {
        std::println("D::");
        D::A *paa = new D::A{};
        D::A *pab = new D::B{};
        D::B *pbb = new D::B{};
        PRINTLN_TYPEID(paa);
        PRINTLN_TYPEID(pab);
        PRINTLN_TYPEID(pbb);
        delete paa;
        delete pab;
        delete pbb;
        std::println();
    }



    {
        std::println("S::");
        S::A *paa = new S::A{};
        S::A *pab = new S::B{};
        S::B *pbb = new S::B{};
        PRINTLN_TYPEID(*paa);
        PRINTLN_TYPEID(*pab);
        PRINTLN_TYPEID(*pbb);
        delete paa;
        delete pab;
        delete pbb;
        std::println();
    }

    {
        std::println("D::");
        D::A *paa = new D::A{};
        D::A *pab = new D::B{};
        D::B *pbb = new D::B{};
        PRINTLN_TYPEID(*paa);
        PRINTLN_TYPEID(*pab);
        PRINTLN_TYPEID(*pbb);
        delete paa;
        delete pab;
        delete pbb;
        std::println();
    }



    {
        std::println("S::");
        const S::A &raa = S::A{};
        const S::A &rab = S::B{};
        const S::B &rbb = S::B{};
        PRINTLN_TYPEID(raa);
        PRINTLN_TYPEID(rab);
        PRINTLN_TYPEID(rbb);
        std::println();
    }

    {
        std::println("D::");
        const D::A &raa = D::A{};
        const D::A &rab = D::B{};
        const D::B &rbb = D::B{};
        PRINTLN_TYPEID(raa);
        PRINTLN_TYPEID(rab);
        PRINTLN_TYPEID(rbb);
        std::println();
    }



}
