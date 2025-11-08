#pragma once 

#include "figure.hpp"
#include "vector.hpp"

#include <memory>
#include <stdexcept>

namespace figure {
template<Scalar T> class Square : public Figure<T> {
    private: 
        std::unique_ptr<Point<T>[]> ver;
    public:
        static constexpr size_t VERTICES_COUNT = 4;

        Square();

        Square(const Point<T> &x1, const Point<T> &x2, const Point<T> &x3, const Point<T> &x4);

        Square(const Square<T> &other);
        
        Square<T> &operator=(const Square<T> &other);
  
        Square(Square<T> &&other) noexcept;

        Square<T> &operator=(Square<T> &&other) noexcept;

        bool operator==(const Square<T> &other) const;

        bool operator!=(const Square<T> &other) const;

        Point<T> GeomCenter() const override;

        double Area() const override;

        operator double() const override;

        void Print(std::ostream& os) const override;

        void Read(std::istream& is) override;

        ~Square() = default;
    private:
        bool isValidSquare() const;
};
}

#include "square.ipp"