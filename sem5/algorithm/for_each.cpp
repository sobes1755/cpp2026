// #include <mdspan>
#include <experimental/mdspan>
#include <vector>
#include <algorithm>
#include <execution>
#include <ranges>
#include <chrono>
#include <random>
#include <numbers>
#include <iostream>

int
main()
{

    constexpr size_t X = 256;
    constexpr size_t Y = 512;
    constexpr size_t Z = 1024;

    std::vector<double> v1(X * Y * Z);
    std::vector<double> v2(X * Y * Z);
    std::vector<double> v3(X * Y * Z);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    std::cout << "Creating v1..." << std::endl;
    for (auto& val : v1) val = dis(gen);
    std::cout << "Creating v2..." << std::endl;
    for (auto& val : v2) val = dis(gen);

    std::cout << "Creating m1..." << std::endl;
    std::mdspan m1{v1.data(), X, Y, Z};
    std::cout << "Creating m2..." << std::endl;
    std::mdspan m2{v2.data(), X, Y, Z};
    std::cout << "Creating m3..." << std::endl;
    std::mdspan m3{v3.data(), X, Y, Z};

    std::cout << "Calculating linear combination: pi * m1 + e * m2..." << std::endl;

    auto grid = std::views::cartesian_product(
        std::views::iota((size_t) 0, X),
        std::views::iota((size_t) 0, Y),
        std::views::iota((size_t) 0, Z));

    // std::execution::seq: runs the algorithm sequentially
    // std::execution::par: runs the algorithm in parallel on multiple threads
    // std::execution::par_unseq: runs the algorithm in parallel on multiple threads
    //     and allows the interleaving of individual loops;
    //     permits a vectorized version with SIMD (Single Instruction Multiple Data) extensions.

    using std::chrono::duration;
    using std::chrono::system_clock;

    // SEQ

    auto swseq = system_clock::now();

    std::for_each(std::execution::seq, grid.begin(), grid.end(), [&](auto tuple) {
        auto [p, q, r] = tuple;
        m3[p, q, r] = std::numbers::pi * m1[p, q, r] + std::numbers::e * m2[p, q, r];
    });
  
    duration<double> dseq = system_clock::now() - swseq;

    std::cout << "seq: " << dseq.count() << " sec" << std::endl;

    // PAR

    auto swpar = system_clock::now();

    std::for_each(std::execution::par, grid.begin(), grid.end(), [&](auto tuple) {
        auto [p, q, r] = tuple;
        m3[p, q, r] = std::numbers::pi * m1[p, q, r] + std::numbers::e * m2[p, q, r];
    });
  
    duration<double> dpar = system_clock::now() - swpar;

    std::cout << "par: " << dpar.count() << " sec" << std::endl;

    // PAR_UNSEQ

    auto swpar_unseq = system_clock::now();

    std::for_each(std::execution::par_unseq, grid.begin(), grid.end(), [&](auto tuple) {
        auto [p, q, r] = tuple;
        m3[p, q, r] = std::numbers::pi * m1[p, q, r] + std::numbers::e * m2[p, q, r];
    });
  
    duration<double> dpar_unseq = system_clock::now() - swpar_unseq;

    std::cout << "par_unseq: " << dpar_unseq.count() << " sec" << std::endl;

}
