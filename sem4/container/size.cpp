#include <map>
#include <set>
#include <vector>

#include <iostream>

int main() {

    std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::set<double> s {std::numbers::e, std::numbers::pi};
    std::map<std::string, int> m {{"a", 1}, {"b", 2}, {"c", 3}};

    std::cout << v.empty() << std::endl;  // false
    std::cout << s.empty() << std::endl;  // false
    std::cout << m.empty() << std::endl;  // false

    std::cout << v.size() << std::endl;  // 10
    std::cout << s.size() << std::endl;  // 2
    std::cout << m.size() << std::endl;  // 3

    std::cout << v.max_size() << std::endl;  // 4611686018427387903
    std::cout << s.max_size() << std::endl;  // 461168601842738790
    std::cout << m.max_size() << std::endl;  // 384307168202282325

    std::cout << "v: ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "s: ";
    for (double val : s)
        std::cout << val << " ";
    std::cout << std::endl;

    std::cout << "m: ";
    for (const auto& [key, value] : m)
        std::cout << key << " " << value << std::endl;
    std::cout << std::endl;

}
