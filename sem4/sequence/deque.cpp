#include <iostream>
#include <deque>

struct DebugInt {

    int value;

    DebugInt(int v) : value(v) { std::cout << "CTR: " << value << std::endl; }
    DebugInt(const DebugInt& o) : value(o.value) { std::cout << "Copy CTR: " << value << std::endl; }
    DebugInt(DebugInt&& o) noexcept : value(o.value) { std::cout << "Move CTR: " << value << std::endl; }

    int operator()() const {
        return value;
    }

};

int main() {

    auto lambda = [](const auto& d, const char* s) {
        std::cout << s << ": ";
        for (auto& o : d) std::cout << o() << " ";
        std::cout << std::endl;
    };

    std::deque<DebugInt> d;

    std::cout << "push_back..." << std::endl;
    d.push_back(10); // DebugInt(10) + move to deque

    std::cout << "emplace_back..." << std::endl;
    d.emplace_back(20); // DebugInt(20) внутри deque

    std::cout << "push_front..." << std::endl;
    d.push_front(30); // DebugInt(30) + move to deque

    std::cout << "emplace_front..." << std::endl;
    d.emplace_front(40); // DebugInt(40) внутри deque

    lambda(d, "d");

}
