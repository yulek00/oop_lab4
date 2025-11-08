#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>
#include "figure.hpp"

namespace vector {

template <class T>
class Vector {
public:
    Vector();

    ~Vector() = default;

    Vector(const Vector& other) = delete;

    Vector& operator=(const Vector& other) = delete;

    Vector(Vector&& other) noexcept;

    Vector& operator=(Vector&& other) noexcept;

    T& operator[](size_t pos);

    const T& operator[](size_t pos) const;

    void PushBack(T&& val);

    void Erase(size_t ind);

    size_t Size() const noexcept;

    bool IsEmpty() const noexcept;

    void Clear();

    void Reserve(size_t new_cap);


private:
    std::unique_ptr<T[]> arr_;
    size_t sz_;
    size_t cap_;
};

}

#include "vector.ipp"