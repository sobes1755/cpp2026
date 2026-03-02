#include <cmath>
#include <iostream>
#include <iomanip>

class Welford1962 {
private:
    size_t size_{0};
    double mean_{0.};
    double sum2_{0.};

public:
    void update(double x) {
        size_ ++;
        double d1 = x - mean_;
        mean_ += d1 / size_;
        double d2 = x - mean_;
        sum2_ += d1 * d2;
    }

    auto size() const noexcept {
        return size_;
    }

    auto mean() const noexcept {
        return mean_;
    }

    auto ubvar() const {
        return (size_ > 1) ? sum2_ / (size_ - 1) : 0.;
    }

    auto bvar() const {
        return (size_ > 0) ? sum2_ / size_ : 0.;
    }

    auto ubdev() const { 
        return std::sqrt(ubvar());
    }

    auto bdev() const { 
        return std::sqrt(bvar());
    }

};

int main() {

    Welford1962 w{};

    double d;

    while (std::cin >> d) {
        w.update(d);
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    std::cout << "Size = " << w.size() << ". \n";
    std::cout << "Mean = " << w.mean() << ". \n";
    std::cout << "Deviation = " << w.bdev() << ".\n";

}
