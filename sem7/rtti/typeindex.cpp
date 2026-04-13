#include <typeindex>
#include <cxxabi.h>
#include <string>
#include <print>
#include <unordered_map>
#include <memory>

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

std::string demangle(const char* name) {

    int status = 0;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    };

    return (status == 0) ? res.get() : name;

}

int
main()
{

    std::unordered_map<std::type_index, std::string> de;  // demangled

    de.insert({ std::type_index(typeid(S::A)), "S::A" });
    de.insert({ std::type_index(typeid(S::B)), "S::B" });
    de.insert({ std::type_index(typeid(D::A)), "D::A" });
    de.insert({ std::type_index(typeid(D::B)), "D::B" });

    S::A sa;
    S::B sb;
    D::A da;
    D::B db;

    std::println("sa -> {}, {}", typeid(sa).name(), de[std::type_index(typeid(sa))]);
    std::println("sb -> {}, {}", typeid(sb).name(), de[std::type_index(typeid(sb))]);
    std::println("da -> {}, {}", typeid(da).name(), de[std::type_index(typeid(da))]);
    std::println("db -> {}, {}", typeid(db).name(), de[std::type_index(typeid(db))]);

    std::println("sa -> {}, {}", typeid(sa).name(), demangle(typeid(sa).name()));
    std::println("sb -> {}, {}", typeid(sb).name(), demangle(typeid(sb).name()));
    std::println("da -> {}, {}", typeid(da).name(), demangle(typeid(da).name()));
    std::println("db -> {}, {}", typeid(db).name(), demangle(typeid(db).name()));

}
