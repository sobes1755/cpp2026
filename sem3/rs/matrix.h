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

    // Gauss

    Matrix<T> solve(const Matrix<T>& B) const {

        if (r_ != c_) throw std::runtime_error("Matrix A must be square!");
        if (r_ != B.r_) throw std::runtime_error("Rows of maxtrix A must match rows of matrix B!");

        Matrix<T> A_tmp = *this;
        Matrix<T> X_tmp = B;

        size_t m = r_;
        size_t nA = c_;
        size_t nX = B.c_;

        for (size_t i = 0; i < m; ++i) {

            size_t i_pivot = i;

            if constexpr (Thasabs<T>) {
                for (size_t k = i + 1; k < m; ++k) {
                    if (std::abs(A_tmp[k, i]) > std::abs(A_tmp[i_pivot, i])) {
                        i_pivot = k;
                    }
                }
            } else {
                for (size_t k = i; k < m; ++k) {
                    if (A_tmp[k, i] != T(0)) {
                        i_pivot = k;
                        break;
                    }
                }
            }

            if (A_tmp[i_pivot, i] == T(0)) {
                throw std::runtime_error("Matrix A must be nonsingular!");
            }

            if (i_pivot != i) {
                for (size_t j = 0; j < nA; ++j) std::swap(A_tmp[i, j], A_tmp[i_pivot, j]);
                for (size_t j = 0; j < nX; ++j) std::swap(X_tmp[i, j], X_tmp[i_pivot, j]);
            }

            T inv_pivot = T(1) / A_tmp[i, i];

            for (size_t j = i; j < nA; ++j) A_tmp[i, j] *= inv_pivot;
            for (size_t j = 0; j < nX; ++j) X_tmp[i, j] *= inv_pivot;

            for (size_t k = i + 1; k < m; ++k) {

                T factor = A_tmp[k, i];

                if (factor != T(0)) {
                    for (size_t j = i; j < nA; ++j) A_tmp[k, j] -= factor * A_tmp[i, j];
                    for (size_t j = 0; j < nX; ++j) X_tmp[k, j] -= factor * X_tmp[i, j];
                }

            }

        }

        for (size_t i = m; i-- > 0;) {

            for (size_t k = i; k-- > 0;) {

                T factor = A_tmp[k, i];

                if (factor != T(0)) {

                    A_tmp[k, i] -= factor * A_tmp[i, i];

                    for (size_t j = 0; j < nX; ++j) {
                        X_tmp[k, j] -= factor * X_tmp[i, j];
                    }

                }

            }

        }

        return X_tmp;

    }

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
