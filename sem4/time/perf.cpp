#include <chrono>
#include <iostream>

int main() {

    std::vector<double> large(1'000'000, -12345.6789);

    std::vector<double> empty1;
    std::vector<double> empty2;

    auto start1 = std::chrono::high_resolution_clock::now();
    empty1 = large;
    auto finish1 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration<double>(finish1 - start1).count();
    std::cout << dur1 << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    empty2 = std::move(large);
    auto finish2 = std::chrono::high_resolution_clock::now();

    auto dur2 = std::chrono::duration<double>(finish2 - start2).count();
    std::cout << dur2 << std::endl;

}
