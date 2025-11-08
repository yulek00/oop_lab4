#pragma once 

namespace figure {

template<Scalar T> 
Square<T>::Square() {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = Point<T>(0, 0);
    ver[1] = Point<T>(1, 0);
    ver[2] = Point<T>(1, 1);
    ver[3] = Point<T>(0, 1);
}

template<Scalar T>
Square<T>::Square(const Point<T> &x1, const Point<T> &x2, const Point<T> &x3, const Point<T> &x4) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = x1;
    ver[1] = x2;
    ver[2] = x3;
    ver[3] = x4;
    if (!isValidSquare()) {
        throw std::invalid_argument("Points do not form a valid Square");
    }
}

template<Scalar T>
Square<T>::Square(const Square<T> &other) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        ver[i] = other.ver[i];
    }
}

template<Scalar T>
Square<T>& Square<T>::operator=(const Square<T> &other) {
    if (this != &other) { 
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
            ver[i] = other.ver[i];
        }
    }
    return *this;
}

template<Scalar T>
Square<T>::Square(Square<T> &&other) noexcept 
    : ver(std::move(other.ver)) {}

template<Scalar T>
Square<T>& Square<T>::operator=(Square<T> &&other) noexcept {
    if (this != &other) {
        ver = std::move(other.ver);
    }
    return *this;
}

template<Scalar T>
bool Square<T>::operator==(const Square<T> &other) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        if (ver[i] != other.ver[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool Square<T>::operator!=(const Square<T> &other) const {
    return !(*this == other);
}

template<Scalar T>
Point<T> Square<T>::GeomCenter() const {
    T center_x = 0, center_y = 0;
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        center_x += ver[i].x;
        center_y += ver[i].y;
    }
    return Point<T>(center_x / VERTICES_COUNT, center_y / VERTICES_COUNT);
}

template<Scalar T>
double Square<T>::Area() const {
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
Square<T>::operator double() const {
    return Area();
}

template<Scalar T>
void Square<T>::Print(std::ostream& os) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        os << "(" << ver[i] << ")";
        if (i < VERTICES_COUNT - 1) os << " ";
    }
}

template<Scalar T>
void Square<T>::Read(std::istream& is) {
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        is >> ver[i];
    }
    if (!isValidSquare()) {
        throw std::invalid_argument("Invalid Square input");
    }
}

template<Scalar T>
bool Square<T>::isValidSquare() const {
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
                        
    double side1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
    double side2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);
    double side3 = std::sqrt(v3.x * v3.x + v3.y * v3.y);
    double side4 = std::sqrt(v4.x * v4.x + v4.y * v4.y);
    
    bool equal_sides = std::abs(side1 - side2) < EPS &&
                      std::abs(side2 - side3) < EPS &&
                      std::abs(side3 - side4) < EPS;
    
    return right_angles && parallel_sides && equal_sides;
}

}