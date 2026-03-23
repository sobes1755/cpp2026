#include <vector>
#include <iostream>

int main() {

    std::vector<int> v1(10);
    std::vector<int> v2{10};
    std::vector<int> v3(10, 207);
    std::vector<int> v4{10, 207};

    auto lambda = [](const auto& v, const char* s) {
        std::cout << s << ": ";
        for (int i : v) std::cout << i << " ";
        std::cout << std::endl;
    };

    lambda(v1, "v1");
    lambda(v2, "v2");
    lambda(v3, "v3");
    lambda(v4, "v4");

    v1.reserve(20);

    std::cout << "v1.size() = " << v1.size() << std::endl;
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;

    v2.resize(30);

    std::cout << "v2.size() = " << v2.size() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << std::endl;

    v1.shrink_to_fit();

    std::cout << "v1.size() = " << v1.size() << std::endl;
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;

    v2.shrink_to_fit();

    std::cout << "v2.size() = " << v2.size() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << std::endl;

}
