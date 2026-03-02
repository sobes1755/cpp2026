#include <iostream>
#include <vector>

template<typename T>
concept Thasabs = requires(T a) {
    { std::abs(a) } -> std::convertible_to<double>; 
};

template <typename T>
class Matrix {
private:

    std::vector<T> data_;
    size_t r_, c_;

    // rows[i] start, finish, [j]...

    struct RowView {

        T *start, *finish;

        T& operator[](size_t j) { return start[j]; }

        T* begin() { return start; }
        T* end() { return finish; }

    };

    // rows[i]...

    struct RowProxy {

        Matrix& m;

        RowView operator[](size_t i) { 
            T* ptr = &m.data_[i * m.c_];
            return { ptr, ptr + m.c_ }; 
        }

        struct MatrixRowsIterator {
            Matrix& m;
            size_t i;
            RowView operator*() { return m.rows[i]; }
            MatrixRowsIterator& operator++() { i++; return *this; }
            bool operator!=(const MatrixRowsIterator& other) const { return i != other.i; }
        };

        MatrixRowsIterator begin() { return { m, 0 }; }
        MatrixRowsIterator end() { return { m, m.r_ }; }

    };

    // cols[j] startr, finish, [i]...

    struct ColView {

        T *start, *finish;
        size_t step;

        T& operator[](size_t i) { return start[i * step]; }

        struct ColItemsIterator {
            T* ptr;
            size_t step;
            T& operator*() { return *ptr; }
            ColItemsIterator& operator++() { ptr += step; return *this; }
            bool operator!=(const ColItemsIterator& other) const { return ptr != other.ptr; }
        };

        ColItemsIterator begin() { return {start, step}; }
        ColItemsIterator end() { return {finish, step}; }

    };

    // cols[j]...

    struct ColProxy {

        Matrix& m;

        ColView operator[](size_t j) { 
            T* ptr = &m.data_[j];
            return { ptr, ptr + m.r_ * m.c_, m.c_ }; 
        }

        struct MatrixColsIterator {
            Matrix& m;
            size_t j;
            ColView operator*() { return m.cols[j]; }
            MatrixColsIterator& operator++() { j++; return *this; }
            bool operator!=(const MatrixColsIterator& other) const { return j != other.j; }
        };

        MatrixColsIterator begin() { return { m, 0 }; }
        MatrixColsIterator end() { return { m, m.c_ }; }

    };

public:

    // rows[i]...
    // cols[j]...

    RowProxy rows;
    ColProxy cols;

    // CTR

    Matrix(size_t r, size_t c) : data_(r * c, T()), r_(r), c_(c), rows{*this}, cols{*this} {}

    // COPY CTR

    Matrix(const Matrix& other) 
        : data_(other.data_), r_(other.r_), c_(other.c_), rows{*this}, cols{*this} {}

    // MOVE CTR

    Matrix(Matrix&& other) noexcept 
        : data_(std::move(other.data_)), r_(other.r_), c_(other.c_), rows{*this}, cols{*this} {
        other.r_ = 0;
        other.c_ = 0;
    }

    // COPY ASSIGNMENT

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data_ = other.data_;
            r_ = other.r_;
            c_ = other.c_;
        }
        return *this;
    }

    // MOVE ASSIGNMENT

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            r_ = other.r_;
            c_ = other.c_;
            other.r_ = 0;
            other.c_ = 0;
        }
        return *this;
    }

    // matrix[i,j] since C++23...

    T& operator[](size_t r, size_t c) { return data_[r * c_ + c]; }

    // Default iterator by cols...

    auto begin() { return cols.begin(); }
    auto end() { return cols.end(); }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {

        for (size_t i = 0; i < mat.r_; ++i) {
            for (size_t j = 0; j < mat.c_; ++j) {
                os << mat.data_[i * mat.c_ + j] << " ";
            }
            os << "\n";
        }

        return os;

    }

};

int main()
{

    Matrix<int> M(3, 3);
    
    M[1, 1] = 1;

    M.rows[0][2] = 2;
    M.cols[0][2] = 3;

    std::cout << "Iterating by cols (default):\n";

    for (auto col : M.cols) {
        std::cout << "col^T = ";
        for (auto v: col) std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "Iterating by rows:\n";

    for (auto row : M.rows) {
        std::cout << "row = ";
        for (auto v : row) std::cout << v << " ";
        std::cout << "\n";
    }

    std::cout << "\n";

    return 0;

}
