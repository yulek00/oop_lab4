#pragma once

namespace figure {

template<Scalar T> 
Trapeze<T>::Trapeze() {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = Point<T>(0, 0);
    ver[1] = Point<T>(2, 0);
    ver[2] = Point<T>(1.5, 1);
    ver[3] = Point<T>(0, 1);
}

template<Scalar T>
Trapeze<T>::Trapeze(const Point<T> &x1, const Point<T> &x2, const Point<T> &x3, const Point<T> &x4) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    ver[0] = x1;
    ver[1] = x2;
    ver[2] = x3;
    ver[3] = x4;
    if (!isValidTrapeze()) {
        throw std::invalid_argument("Points do not form a valid Trapeze");
    }
}

template<Scalar T>
Trapeze<T>::Trapeze(const Trapeze<T> &other) {
    ver = std::make_unique<Point<T>[]>(VERTICES_COUNT);
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        ver[i] = other.ver[i];
    }
}

template<Scalar T>
Trapeze<T>& Trapeze<T>::operator=(const Trapeze<T> &other) {
    if (this != &other) { 
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
            ver[i] = other.ver[i];
        }
    }
    return *this;
}

template<Scalar T>
Trapeze<T>::Trapeze(Trapeze<T> &&other) noexcept 
    : ver(std::move(other.ver)) {}

template<Scalar T>
Trapeze<T>& Trapeze<T>::operator=(Trapeze<T> &&other) noexcept {
    if (this != &other) {
        ver = std::move(other.ver);
    }
    return *this;
}

template<Scalar T>
bool Trapeze<T>::operator==(const Trapeze<T> &other) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        if (ver[i] != other.ver[i]) {
            return false;
        }
    }
    return true;
}

template<Scalar T>
bool Trapeze<T>::operator!=(const Trapeze<T> &other) const {
    return !(*this == other);
}

template<Scalar T>
Point<T> Trapeze<T>::GeomCenter() const {
    T center_x = 0, center_y = 0;
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        center_x += ver[i].x;
        center_y += ver[i].y;
    }
    return Point<T>(center_x / VERTICES_COUNT, center_y / VERTICES_COUNT);
}

template<Scalar T>
double Trapeze<T>::Area() const {
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
Trapeze<T>::operator double() const {
    return Area();
}

template<Scalar T>
void Trapeze<T>::Print(std::ostream& os) const {
        for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        os << "(" << ver[i] << ")";
        if (i < VERTICES_COUNT - 1) os << " ";
    }
}

template<Scalar T>
void Trapeze<T>::Read(std::istream& is) {
    for (size_t i = 0; i < VERTICES_COUNT; ++i) {
        is >> ver[i];
    }
    if (!isValidTrapeze()) {
        throw std::invalid_argument("Invalid Trapeze input");
    }
}

template<Scalar T>
bool Trapeze<T>::isValidTrapeze() const {
    Point<T> AB = Point<T>(ver[1].x - ver[0].x, ver[1].y - ver[0].y);
    Point<T> BC = Point<T>(ver[2].x - ver[1].x, ver[2].y - ver[1].y);
    Point<T> CD = Point<T>(ver[3].x - ver[2].x, ver[3].y - ver[2].y);
    Point<T> DA = Point<T>(ver[0].x - ver[3].x, ver[0].y - ver[3].y);

    bool bases_parallel = std::abs(AB.x * CD.y - AB.y * CD.x) < EPS;

    bool alt_bases_parallel = std::abs(DA.x * BC.y - DA.y * BC.x) < EPS;

    if (!(bases_parallel ^ alt_bases_parallel)) {
        return false; 
    }

    if (bases_parallel) {
        double BC_length = std::sqrt(BC.x * BC.x + BC.y * BC.y);
        double DA_length = std::sqrt(DA.x * DA.x + DA.y * DA.y);
        return std::abs(BC_length - DA_length) < EPS;
    } else {
        double AB_length = std::sqrt(AB.x * AB.x + AB.y * AB.y);
        double CD_length = std::sqrt(CD.x * CD.x + CD.y * CD.y);
        return std::abs(AB_length - CD_length) < EPS;
    }
}

}