#include <list>
#include <compare>
#include <iostream>

struct DebugInt {

    int value;

    DebugInt(int v) : value(v) { std::cout << "CTR: " << value << std::endl; }
    DebugInt(const DebugInt& o) : value(o.value) { std::cout << "Copy CTR: " << value << std::endl; }
    DebugInt(DebugInt&& o) noexcept : value(o.value) { std::cout << "Move CTR: " << value << std::endl; }
    ~DebugInt() { std::cout << "DTR: " << value << std::endl; }

    auto operator<=>(const DebugInt& other) const {
        std::cout << "<=>: " << value << " vs " << other.value << "?" << std::endl;
        return value <=> other.value;
    }

    bool operator==(const DebugInt& other) const = default;

    int operator()() const { return value; }

};

int main() {

    auto lambda = [](const auto& d, const char* s) {
        std::cout << s << ": ";
        for (auto& o : d) std::cout << o() << " ";
        std::cout << std::endl;
    };

    std::list<DebugInt> list1{15, 2, 18, 19, 4, 15, 1, 3, 18, 5, 4, 7, 17, 9, 16, 8, 6, 6, 17, 1, 2};
    std::list<DebugInt> list2{10, 11, 12, 13, 14};

    lambda(list1, "list1");
    lambda(list2, "list2");

    list1.sort();

    lambda(list1, "list1");

    list1.unique();

    lambda(list1, "list1");

    list1.splice(std::lower_bound(list1.begin(), list1.end(), DebugInt(15)), list2);

    lambda(list1, "list1");
    lambda(list2, "list2");

}
