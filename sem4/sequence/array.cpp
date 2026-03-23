#include <array>

#include <iostream>

int main() {

    std::array<int, 10> a1;  // All the 10 elements are not initialized not initialized.
    std::array<int, 10> a2{};  // All the 10 elements are default initialized.
    std::array<int, 10> a3{1, 2, 3, 4, 5};  // The remaining 5 elements are default initialized.

    std::cout << "a1: ";
    for (int i : a1) std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "a2: ";
    for (int i : a2) std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "a3: ";
    for (int i : a3) std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "a3[1] = " << a3[1] << std::endl;
    std::cout << "a3.at(1) = " << a3.at(1) << std::endl;
    std::cout << "get<1>(a3) = " << get<1>(a3) << std::endl;

}
