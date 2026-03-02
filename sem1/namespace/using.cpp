#include :q<numbers>
#include <print>

namespace num = std::numbers;

namespace {
    int xxx {10};
}

int xxx;

namespace std {
    int yyy {20};
}

int main()
{

    using std::println;
    using std::numbers::pi;

    // using namespace std;
    // using namespace std::numbers;

    double pi8 = pi;

    println("Double pi: {}.", pi8);

    float pi4 = num::pi_v<float>;
    long double pi16 = num::pi_v<long double>;

    println("Float pi: {}.", pi4);
    println("Long double pi: {}.", pi16);

    println("xxx = {}", ::xxx);

}
