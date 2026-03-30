#include <map>
#include <unordered_map>
#include <iostream>

int main() {

    auto lambda = [](const auto& m, const char* s) {
        std::cout << s << ": ";
        for (auto& p : m) std::cout << "{\"" << p.first << "\", " << p.second << "} " << std::endl;
    };

    // Ordered map...

    std::map<std::string, int> m {{"Dijkstra", 1972}, {"Scott", 1976}};

    lambda(m, "m");

    m["Ritchie"] = 1983;

    lambda(m, "m");

    m.erase("Scott");

    lambda(m, "m");

    m.clear();

    std::cout << "m.size() = " << m.size() << std::endl;

    // Unordered map...

    std::unordered_map<std::string, int> um {{"Dijkstra", 1972}, {"Scott", 1976}};
 
    lambda(um, "um");

    um["Ritchie"]= 1983;

    lambda(um, "um");

    um.erase("Scott");

    lambda(um, "um");

    um.clear();

    std::cout << "um.size() = " << um.size() << std::endl;

}
