#include <numbers>
#include <print>

namespace num = std::numbers;

int main()
{

    double pi8 = std::numbers::pi;

    std::println("Double pi: {}.", pi8);

    float pi4 = num::pi_v<float>;
    long double pi16 = num::pi_v<long double>;

    std::println("Float pi: {}.", pi4);
    std::println("Long double pi: {}.", pi16);

}
