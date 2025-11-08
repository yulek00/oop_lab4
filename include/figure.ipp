#pragma once

#include <cmath>

namespace figure {
    template <Scalar T>
    Point<T>::Point(T x, T y) : x(x), y(y) {}

    template <Scalar T>
    bool operator==(const Point<T> &lp, const Point<T> &rp) {
        return std::abs(lp.x - rp.x) < EPS && std::abs(lp.y - rp.y) < EPS;
    }

    template <Scalar T>
    bool operator!=(const Point<T> &lp, const Point<T> &rp) {
        return !(lp == rp);
    }

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Point<T> &point) {
        os << point.x << " " << point.y;
        return os;
    }

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Point<T> &point) {
        is >> point.x >> point.y;
        return is;
    }

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Figure<T> &fig) {
        fig.Print(os);
        return os;
    }

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Figure<T> &fig) {
        fig.Read(is);
        return is;
    }
}
