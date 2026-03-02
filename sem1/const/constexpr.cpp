#include <iostream>
#include <print>

constexpr int square(int n) {
    return n * n;
}

int main()
{

    conste:xpr int a = 207;
    constexpr int asquare = square(a); // compile-time calculation

    static_assert(asquare == 42849, "Failed to calculate asquare!");

    std::println("{}^2 = {}!", a, asquare);

    int b; std::cin >> b;
    int bsquare = square(b); // run-time calculation

    std::println("{}^2 = {}!", b, bsquare);

}
