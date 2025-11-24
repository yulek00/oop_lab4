#pragma once 

#include "figure.hpp"
#include "vector.hpp"

#include <memory>
#include <stdexcept>

namespace figure {
template<Scalar T> class Trapeze : public Figure<T> {
    private: 
        std::unique_ptr<Point<T>[]> ver;
    public:
        static constexpr size_t VERTICES_COUNT = 4;
        
        Trapeze();

        Trapeze(const Point<T> &x1, const Point<T> &x2, const Point<T> &x3, const Point<T> &x4);

        Trapeze(const Trapeze<T> &other);
        
        Trapeze<T> &operator=(const Trapeze<T> &other);
  
        Trapeze(Trapeze<T> &&other) noexcept;

        Trapeze<T> &operator=(Trapeze<T> &&other) noexcept;

        bool operator==(const Trapeze<T> &other) const;

        bool operator!=(const Trapeze<T> &other) const;

        Point<T> GeomCenter() const override;

        double Area() const override;

        operator double() const override;

        void Print(std::ostream& os) const override;

        void Read(std::istream& is) override;

        ~Trapeze() = default;
    private:
        bool isValidTrapeze() const;
};
}

#include "trapeze.ipp"