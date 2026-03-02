#include <iostream>
#include <array>
#include <compare>

template <int M>
class GFprime {
private:

    int value_;

public:

    constexpr GFprime(int value = 0) : value_{value} {}

    constexpr GFprime& operator+=(const GFprime& other) {
        value_ += other.value_;
        if (value_ >= M) value_ -= M;
        return *this;
    }

    constexpr GFprime& operator-=(const GFprime& other) {
        value_ -= other.value_;
        if (value_ < 0) value_ += M;
        return *this;
    }

    constexpr GFprime& operator*=(const GFprime& other) {
        value_ = tables_.mul_[value_][other.value_];
        return *this;
    }

    constexpr GFprime& operator/=(const GFprime& other) {
        value_ = tables_.mul_[value_][tables_.inv_[other.value_]];
        return *this;
    }

    // spaceship operator since C++20...

    constexpr std::strong_ordering operator<=>(const GFprime& other) const noexcept {
        if (value_ < other.value_) return std::strong_ordering::less;
        if (value_ > other.value_) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    constexpr bool operator==(const GFprime& other) const noexcept {
        return value_ == other.value_;
    }

    friend constexpr GFprime operator+(GFprime a, const GFprime& b) { return a += b; }
    friend constexpr GFprime operator-(GFprime a, const GFprime& b) { return a -= b; }
    friend constexpr GFprime operator*(GFprime a, const GFprime& b) { return a *= b; }
    friend constexpr GFprime operator/(GFprime a, const GFprime& b) { return a /= b; }

    friend std::ostream& operator<<(std::ostream& os, const GFprime& v) { return os << v.value_; }  // explicit inline is better sometimes...

private:

    struct Tables {

        std::array<std::array<int, M>, M> mul_{};
        std::array<int, M> inv_{};

        constexpr Tables() {

            for (int i = 1; i < M; ++i) {
                for (int j = 1; j < M; ++j) {
                    mul_[i][j] = (i * j) % M;  // = static_cast<int>((1LL * i * j) % M); is better to avoid UB...
                    if (mul_[i][j] == 1) inv_[i] = j;
                }
            }

        }

    };

    static constexpr Tables tables_{}; 

};
