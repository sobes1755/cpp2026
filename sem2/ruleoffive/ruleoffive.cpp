#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>

class R5 {
private:
    size_t size_;
    char c_;
    char* data_;

public:
    explicit R5(size_t size, char c) : size_(size), c_{c} {

        data_ = new char[size_];

        std::fill(data_, data_ + size_, c);

        std::cout << "CTR (" << __PRETTY_FUNCTION__ << ") created " << size_ << " bytes '" << c_ << "'.\n";

    }

    ~R5() {

        delete[] data_;

        std::cout << "DTR (" << __PRETTY_FUNCTION__ << ") destroyed " << size_ << " bytes '" << c_ << "'.\n";

    }

    R5(const R5& other) : size_{other.size_} {

        data_ = new char[size_];
        std::memcpy(data_, other.data_, size_);

        std::cout << "Copy CTR (" << __PRETTY_FUNCTION__ << ") executed.\n";

    }

    R5& operator=(const R5& other) {

        if (this != &other) {

            delete[] data_;

            size_ = other.size_;
            data_ = new char[size_];
            std::memcpy(data_, other.data_, other.size_);

            std::cout << "Copy ASGN (" << __PRETTY_FUNCTION__ << ") executed.\n";

        }

        return *this;

    }

    R5(R5&& other) noexcept : size_(other.size_), data_(other.data_) {

        other.size_ = 0;
        other.data_ = nullptr;

        std::cout << "Move CTR (" << __PRETTY_FUNCTION__ << ") executed.\n";

    }

    R5& operator=(R5&& other) noexcept {

        if (this != &other) {

            delete[] data_;

            size_ = other.size_;
            data_ = other.data_;

            other.size_ = 0;
            other.data_ = nullptr;

            std::cout << "Move ASGN (" << __PRETTY_FUNCTION__ << ") executed.\n";

        }

        return *this;

    }

    R5 operator+(const R5& other) const {

        size_t size = std::min(this->size_, other.size_);

        R5 result(size, this->c_ + other.c_);

        for (size_t k = 0; k < result.size_; ++k) {
            result.data_[k] = this->data_[k] + other.data_[k];
        }

        std::cout << "Operator + (" << __PRETTY_FUNCTION__ << ") executed.\n";

        return result; // RVO (return value optimization) or mvoe

    }

    auto operator()() const {
        return size_;
    }

};

int main() {

    R5 a(1024, 'a');
    R5 b(2048, 'b');

    std::cout << "a() == " << a() << "\n";
    std::cout << "b() == " << b() << "\n\n";

    R5 c = a;             // Copy CTR
    R5 d = std::move(b);  // Move CTR
    R5 z = R5(10, 'Z');

    std::cout << "a() == " << a() << "\n";
    std::cout << "b() == " << b() << "\n";
    std::cout << "c() == " << c() << "\n";
    std::cout << "d() == " << d() << "\n\n";

    R5 e(4096, 'e');
    R5 f(8192, 'f');

    std::cout << "a() == " << a() << "\n";
    std::cout << "b() == " << b() << "\n";
    std::cout << "c() == " << c() << "\n";
    std::cout << "d() == " << d() << "\n";
    std::cout << "e() == " << e() << "\n";
    std::cout << "f() == " << f() << "\n\n";

    e = c;                       // Copy ASGN
    f = std::move(d);            // Move ASGN

    std::cout << "a() == " << a() << "\n";
    std::cout << "b() == " << b() << "\n";
    std::cout << "c() == " << c() << "\n";
    std::cout << "d() == " << d() << "\n";
    std::cout << "e() == " << e() << "\n";
    std::cout << "f() == " << f() << "\n\n";

    R5 sum = a + R5(65535, '\0');  // Operator +
   
    std::cout << "sum() == " << sum() << "\n\n";

    return EXIT_SUCCESS;

}

