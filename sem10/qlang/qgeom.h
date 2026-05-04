#pragma once

#include <iostream>
#include <cmath>
#include <concepts>

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic T, int size>
struct Storage {

    T data[size] = {};

};

template<arithmetic T>
struct Storage<T, 3> {

    union {
        T data[3];
        struct { T x, y, z; };
    };

    constexpr Storage() : data{0, 0, 0} {}
    constexpr Storage(T x, T y, T z) : x{x}, y{y}, z{z} {}

};

template<arithmetic T>
struct Storage<T, 4> {

    union {
        T data[4];
        struct { T w, x, y, z; };
    };

    constexpr Storage() : data{0, 0, 0, 0} {}
    constexpr Storage(T w, T x, T y, T z) : w{w}, x{x}, y{y}, z{z} {}

};

template<arithmetic T, int size>
class Vector : public Storage<T, size> {
public:

    using Storage<T, size>::Storage;

    constexpr Vector operator+(const Vector& other) const {
        Vector res{};
        for (int i = 0; i < size; ++i) res.data[i] = this->data[i] + other.data[i];
        return res;
    }

    constexpr Vector operator-(const Vector& other) const {
        Vector res{};
        for (int i = 0; i < size; ++i) res.data[i] = this->data[i] - other.data[i];
        return res;
    }

    constexpr Vector operator*(T scalar) const {
        Vector res{};
        for (int i = 0; i < size; ++i) res.data[i] = this->data[i] * scalar;
        return res;
    }

    constexpr Vector operator/(T scalar) const {
        Vector res{};
        for (int i = 0; i < size; ++i) res.data[i] = this->data[i] / scalar;
        return res;
    }

    constexpr T norm() const {
        T res{};
        for (int i = 0; i < size; ++i) res += this->data[i] * this->data[i];
        return std::sqrt(res);
    }

    constexpr T normsquared() const {
        T res{};
        for (int i = 0; i < size; ++i) res += this->data[i] * this->data[i];
        return res;
    }

};

template<arithmetic T>
class Vector3D : public Vector<T, 3> {
public:

    using Vector<T, 3>::Vector;

    constexpr Vector3D(const Vector<T, 3>& base) : Vector<T, 3>(base) {}

    constexpr T dot(const Vector3D& v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    constexpr Vector3D cross(const Vector3D& v) const {
        return {
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x
        };
    }

};

template<arithmetic T>
class Quaternion : public Vector<T, 4> {
public:

    using Vector<T, 4>::Vector;

    constexpr Quaternion(const Vector<T, 4>& base) : Vector<T, 4>(base) {}

    constexpr Quaternion operator*(T scalar) const {
        return { this->w * scalar, this->x * scalar, this->y * scalar, this->z * scalar };
    }

    constexpr Quaternion operator/(T scalar) const {
        return { this->w / scalar, this->x / scalar, this->y / scalar, this->z / scalar };
    }

    constexpr Quaternion conjugate() const {
        return { this->w, -this->x, -this->y, -this->z };
    }

    constexpr Quaternion inverse() const {
        return this->conjugate() / this->normsquared();
    }

    constexpr Quaternion operator*(const Quaternion& q) const {
        return {
            this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z,
            this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
            this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,
            this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w
        };
    }

    constexpr Quaternion operator/(const Quaternion& q) const {
        return (*this) * q.inverse(); // Обязательно точка
    }

};

template<arithmetic T, int size>
std::ostream& 
operator<<(std::ostream& os, const Vector<T, size>& v) {

    os << "[";
    for (int i = 0; i < size; ++i) {
        os << v.data[i] << (i  < size - 1 ? ", " : "");
    }
    return os << "]";

}
