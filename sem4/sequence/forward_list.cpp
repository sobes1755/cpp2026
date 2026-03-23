#include <iostream>
#include <forward_list>
#include <compare>  // <=>
#include <algorithm>

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

    std::forward_list<DebugInt> l1 = {11, -12, -91, 92};
    std::forward_list<DebugInt> l2 = {21, -22, -81, 82};

    l1.push_front(44);
    l2.push_front(66);

    lambda(l1, "l1");
    lambda(l2, "l2");

    l1.sort(); 
    l2.sort();

    lambda(l1, "l1");
    lambda(l2, "l2");

    l1.merge(l2);

    lambda(l1, "l1");
    lambda(l2, "l2");

    l1.remove_if([](const auto& o) { 
        return o() % 2 == 0; 
    });

    lambda(l1, "l1");
    lambda(l2, "l2");

}
          
