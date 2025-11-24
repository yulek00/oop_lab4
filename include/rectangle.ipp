#pragma once

namespace figure {

template<Scalar T> 
Rectangle<T>::Rectangle() {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = Point<T>(0, 0);
    ver[1] = Point<T>(1, 0);
    ver[2] = Point<T>(1, 1);
    ver[3] = Point<T>(0, 1);
}

template<Scalar T>
Rectangle<T>::Rectangle(const Point<T> &x1, const Point<T> &x2, const Point<T> &x3, const Point<T> &x4) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = x1;
    ver[1] = x2;
    ver[2] = x3;
    ver[3] = x4;
    if (!isValidRectangle()) {
        throw std::invalid_argument("Points do not form a valid rectangle");
    }
}

template<Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T> &other) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        ver[i] = other.ver[i];
    }
}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T> &other) {
    if (this != &other) { 
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
            ver[i] = other.ver[i];
        }
    }
    return *this;
}

template<Scalar T>
Rectangle<T>::Rectangle(Rectangle<T> &&other) noexcept 
    : ver(std::move(other.ver)) {}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T> &&other) noexcept {
    if (this != &other) {
        ver = std::move(other.ver);
    }
    return *this;
}

template<Scalar T>
bool Rectangle<T>::operator==(const Rectangle<T> &other) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        if (ver[i] != other.ver[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool Rectangle<T>::operator!=(const Rectangle<T> &other) const {
    return !(*this == other);
}

template<Scalar T>
Point<T> Rectangle<T>::GeomCenter() const {
    T center_x = 0, center_y = 0;
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        center_x += ver[i].x;
        center_y += ver[i].y;
    }
    return Point<T>(center_x / VERTICES_COUNT, center_y / VERTICES_COUNT);
}

template<Scalar T>
double Rectangle<T>::Area() const {
    double area = 0.0;
        int n = VERTICES_COUNT;
        for (size_t i = 0; i < n; ++i) {
            size_t j = (i + 1) % n;  
            area += ver[i].x * ver[j].y;
            area -= ver[i].y * ver[j].x;
        }
        
        return std::abs(area) / 2.0;
    }

template<Scalar T>
Rectangle<T>::operator double() const {
    return Area();
}

template<Scalar T>
void Rectangle<T>::Print(std::ostream& os) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        os << "(" << ver[i] << ")";
        if (i < VERTICES_COUNT - 1) os << " ";
    }
}

template<Scalar T>
void Rectangle<T>::Read(std::istream& is) {
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        is >> ver[i];
    }
    if (!isValidRectangle()) {
        throw std::invalid_argument("Invalid rectangle input");
    }
}

template<Scalar T>
bool Rectangle<T>::isValidRectangle() const {
    Point<T> v1 = Point<T>(ver[1].x - ver[0].x, ver[1].y - ver[0].y);
    Point<T> v2 = Point<T>(ver[2].x - ver[1].x, ver[2].y - ver[1].y);
    Point<T> v3 = Point<T>(ver[3].x - ver[2].x, ver[3].y - ver[2].y);
    Point<T> v4 = Point<T>(ver[0].x - ver[3].x, ver[0].y - ver[3].y);

    bool right_angles = std::abs(v1.x * v2.x + v1.y * v2.y) < EPS &&
                       std::abs(v2.x * v3.x + v2.y * v3.y) < EPS &&
                       std::abs(v3.x * v4.x + v3.y * v4.y) < EPS &&
                       std::abs(v4.x * v1.x + v4.y * v1.y) < EPS;
    
    bool parallel_sides = std::abs(v1.x * v3.y - v1.y * v3.x) < EPS &&
                         std::abs(v2.x * v4.y - v2.y * v4.x) < EPS;
    
    return right_angles && parallel_sides;
}

}