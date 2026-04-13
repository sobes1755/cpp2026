#include <typeinfo>
#include <string>
#include <print>

namespace D1 {

    struct A {
        int a_{};
        A(const int a) : a_{a} {};
        virtual ~A() = default;
    };

    struct B : A {
        std::string b_{};
        B(const int a, const std::string& b) : A{a}, b_{b} {};
    };

}

namespace D2 {

    struct A {
        int a_{};
        A(const int a) : a_{a} {};
        virtual ~A() = default;
    };

    struct B : A {
        std::string b_{};
        B(const int a, const std::string& b) : A{a}, b_{b} {};
    };

}

int
main()
{

    D1::A a1{1};
    D1::B b1{11, "eleven"};

    D2::A a2{2};
    D2::B b2{22, "twenty two"};

    D1::A *pd1a = &b1;
    std::println("pd1a->a_ = {}", pd1a->a_);
    D2::A *pd2a = &b2;
    std::println("pd2a->a_ = {}", pd2a->a_);

    D1::A &rd1a = b1;
    std::println("rd1a.a_ = {}", rd1a.a_);
    D2::A &rd2a = b2;
    std::println("rd2a.a_ = {}", rd2a.a_);

    // static cast

    // D1::B *pd1b = pd1a;  // invalid conversion from ‘D1::A*’ to ‘D1::B*’

    if (typeid(*pd1a) == typeid(D1::B)) {
        D1::B *pd1b = static_cast<D1::B*>(pd1a);
        std::println("pd1b->a_ = {}, pd1b->b_ = {}", pd1b->a_, pd1b->b_);
    }

    // D2::B *pd2b = pd2a;  // invalid conversion from ‘D2::A*’ to ‘D2::B*’

    if (typeid(*pd2a) == typeid(D2::B)) {
        D2::B *pd2b = static_cast<D2::B*>(pd2a);
        std::println("pd2b->a_ = {}, pd2b->b_ = {}", pd2b->a_, pd2b->b_);
    }

    // dynamic cast with pointers

    {

    D1::B *pd1b1 = dynamic_cast<D1::B *>(pd1a);
    D1::B *pd1b2 = dynamic_cast<D1::B *>(pd2a);
    D2::B *pd2b1 = dynamic_cast<D2::B *>(pd1a);
    D2::B *pd2b2 = dynamic_cast<D2::B *>(pd2a);

    std::println("pd1b1 = {}, pd1b2 = {}", static_cast<void *>(pd1b1), static_cast<void *>(pd1b2));
    std::println("pd2b1 = {}, pd2b2 = {}", static_cast<void *>(pd2b1), static_cast<void *>(pd2b2));

    std::println("pd1b1->a_ = {}, pd1b1->b_ = {}", pd1b1->a_, pd1b1->b_);
    std::println("pd2b2->a_ = {}, pd2b2->b_ = {}", pd2b2->a_, pd2b2->b_);

    }

    // dynamic cast with references

    {

    D1::B &rd1b1 = dynamic_cast<D1::B &>(rd1a);
//    [[maybe_unused]] D1::B &rd1b2 = dynamic_cast<D1::B &>(rd2a);
//    [[maybe_unused]] D2::B &rd2b1 = dynamic_cast<D2::B &>(rd1a);
    D2::B &rd2b2 = dynamic_cast<D2::B &>(rd2a);

    std::println("rd1b1.a_ = {}, rd1b1.b_ = {}", rd1b1.a_, rd1b1.b_);
    std::println("rd2b2.a_ = {}, rd2b2.b_ = {}", rd2b2.a_, rd2b2.b_);

    }

    // reinterpret_cast with pointers

    {

    D1::B *pd1b2 = reinterpret_cast<D1::B *>(pd2a);
    D2::B *pd2b1 = reinterpret_cast<D2::B *>(pd1a);

    std::println("pd1b2 = {}", static_cast<void *>(pd1b2));
    std::println("pd2b1 = {}", static_cast<void *>(pd2b1));

    std::println("pd1b2->a_ = {}, pd1b2->b_ = {}", pd1b2->a_, pd1b2->b_);
    std::println("pd2b1->a_ = {}, pd2b1->b_ = {}", pd2b1->a_, pd2b1->b_);

    }

    // reinterpret_cast with references

    {

    D1::B &rd1b2 = reinterpret_cast<D1::B &>(rd2a);
    D2::B &rd2b1 = reinterpret_cast<D2::B &>(rd1a);

    std::println("rd1b2.a_ = {}, pd1b2.b_ = {}", rd1b2.a_, rd1b2.b_);
    std::println("rd2b1.a_ = {}, pd2b1.b_ = {}", rd2b1.a_, rd2b1.b_);

    }

}
