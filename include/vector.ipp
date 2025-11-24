#include <algorithm>

namespace vector {

template <class T>
Vector<T>::Vector() :  arr_(nullptr), sz_(0), cap_(0) {}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept 
    : arr_(std::move(other.arr_)), sz_(other.sz_), cap_(other.cap_) {
    other.sz_ = 0;
    other.cap_ = 0;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        arr_ = std::move(other.arr_);
        sz_ = other.sz_;
        cap_ = other.cap_;
        other.sz_ = 0;
        other.cap_ = 0;
    }
    return *this;
}

template <class T>
T& Vector<T>::operator[](size_t pos) {
    if (pos >= sz_) {
        throw std::out_of_range("Vector index out of range");
    }
    return arr_[pos];
}

template <class T>
const T& Vector<T>::operator[](size_t pos) const {
    if (pos >= sz_) {
        throw std::out_of_range("Vector index out of range");
    }
    return arr_[pos];
}

template <class T>
void Vector<T>::PushBack(T&& val) {
    if (cap_ == sz_) {
        size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
        Reserve(new_cap);
    }
    arr_[sz_] = std::move(val);  
    ++sz_;
}

template <class T>
void Vector<T>::Erase(size_t ind) {
    if (ind >= sz_) {
        throw std::out_of_range("Erase index out of range");
    }

    for (size_t i = ind + 1; i < sz_; ++i) {
        arr_[i - 1] = std::move(arr_[i]);
    }
    --sz_;
}

template <class T>
size_t Vector<T>::Size() const noexcept {
    return sz_;
}

template <class T>
bool Vector<T>::IsEmpty() const noexcept {
    return sz_ == 0;
}

template <class T>
void Vector<T>::Clear() {
    sz_ = 0;
}

template <class T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap <= cap_) {
        return;
    }
    std::shared_ptr<T[]> new_arr(new T[new_cap], std::default_delete<T[]>());
    
    for (size_t i = 0; i < sz_; ++i) {
        new_arr[i] = std::move(arr_[i]);
    }
    
    arr_ = std::move(new_arr);
    cap_ = new_cap;
}
}