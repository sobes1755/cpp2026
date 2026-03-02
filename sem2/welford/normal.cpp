#include <iostream>
#include <random>
#include <cmath>
#include <charconv>
#include <cstring>  // std::strlen

int main(int argc, char* argv[]) {

    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " mean deviation size\n";
        return EXIT_FAILURE;
    }

    double mean;
    double deviation;
    size_t size;

    auto parse = [](const char* first, auto& value) {

        const char* last = first + std::strlen(first);
        auto [ptr, ec] = std::from_chars(first, last, value);

        return ec == std::errc{} && ptr == last;

    };

    if (! parse(argv[1], mean)) {
        std::cerr << "Error: bad mean!\n";
        return EXIT_FAILURE;
    }
    if (! parse(argv[2], deviation)) {
        std::cerr << "Error: bad deviation\n";
        return EXIT_FAILURE;
    }
    if (! parse(argv[3], size)) {
        std::cerr << "Error: bad size!\n";
        return EXIT_FAILURE;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, deviation);

    for (size_t k = 0; k < size; ++k) {
        std::cout << dist(gen) << "\n";
    }

    return EXIT_SUCCESS;
}

