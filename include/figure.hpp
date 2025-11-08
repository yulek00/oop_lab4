#pragma once

#include "concepts.hpp"

#include <iostream>

namespace figure {

    constexpr const double EPS = 1e-9;

    template <Scalar T> class Point {
        public:
            T x = 0;
            T y = 0;
            Point() = default;
            Point(T x, T y);
    };

    template <Scalar T>
    bool operator==(const Point<T> &lp, const Point<T> &rp);

    template <Scalar T>
    bool operator!=(const Point<T> &lp, const Point<T> &rp);
    
    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Point<T> &point);

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Point<T> &point);

    template <Scalar T> class Figure {
        public:
            static constexpr size_t VERTICES_COUNT = 0;
            virtual Point<T> GeomCenter() const = 0;
            virtual double Area() const = 0;
            virtual operator double() const = 0;
            virtual void Print(std::ostream& os) const = 0;
            virtual void Read(std::istream& is) = 0;
            virtual ~Figure() = default;  
    };
    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Figure<T> &fig);

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Figure<T> &fig);
}

#include "figure.ipp"