#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>

class R5 {
private:
    size_t size_;
    char* data_;

public:
    explicit R5(size_t size, char c) : size_(size) {

        data_ = new char[size_];

        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist(0, 255);

        for (size_t k = 0; k < size_; ++k) {
            data_[k] = static_cast<char>(dist(gen));
        }

        std::cout << "CTR (" << __PRETTY_FUNCTION__ << ") created " << size_ << " bytes.\n";

    }

    ~R5() {

        delete[] data_;

        std::cout << "DTR (" << __PRETTY_FUNCTION__ << ")  destroyed " << size_ << " bytes.\n";

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

        R5 result(size);

        for (size_t k = 0; k < result.size_; ++k) {
            result.data_[k] = this->data_[k] + other.data_[k];
        }

        return result; // RVO (return value optimization) or mvoe

    }

    char operator()() const {

        size_t count[256] = {0};

        for (size_t k = 0; k < size_; ++k) {
            count[static_cast<unsigned char>(data_[k])] ++;
        }

        size_t imax = 0;
        for (size_t i = 1; i < 256; ++i) {
            if (count[i] > count[imax]) imax = i;
        }

        return static_cast<char>(imax);

    }

};

int main() {

    std::cout << "CTR:\n";

    R5 b1(1024);
    R5 b2(1024);

    std::cout << "Copy CTR & Move CTR:\n";

    R5 b3 = b1;             // Copy CTR
    R5 b4 = std::move(b2);  // Move CTR

    std::cout << "Copy ASGN & Move ASGN:\n";

    R5 b5(10);

    b5 = b3;                       // Copy ASGN
    b5 = std::move(b4);            // Move ASGN

    std::cout << "Operator +:\n";

    R5 sum = b1 + b5;       // Operator +
   
    std::cout << "Operator ():\n";

    std::cout << sum() << "\n";

    return EXIT_SUCCESS;

}

