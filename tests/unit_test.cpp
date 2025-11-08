#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "rectangle.hpp"
#include "square.hpp"
#include "trapeze.hpp"
#include "vector.hpp"

using namespace figure;
using namespace vector;

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> rect;
    EXPECT_NO_THROW(rect.Area());
    EXPECT_NO_THROW(rect.GeomCenter());
}

TEST(RectangleTest, AreaCalculation) {
    Point<double> p1(0,0), p2(2,0), p3(2,1), p4(0,1);
    Rectangle<double> rect(p1, p2, p3, p4);
    EXPECT_NEAR(rect.Area(), 2.0, figure::EPS);  
}

TEST(RectangleTest, CenterCalculation) {
    Point<double> p1(0,0), p2(2,0), p3(2,2), p4(0,2);
    Rectangle<double> rect(p1, p2, p3, p4);
    Point<double> center = rect.GeomCenter();
    EXPECT_NEAR(center.x, 1.0, figure::EPS);  
    EXPECT_NEAR(center.y, 1.0, figure::EPS); 
}

TEST(RectangleTest, InvalidRectangle) {
    Point<double> p1(0,0), p2(1,0), p3(2,1), p4(0,1);
    EXPECT_THROW(Rectangle<double> rect(p1, p2, p3, p4), std::invalid_argument);
}

TEST(SquareTest, DefaultConstructor) {
    Square<double> square;
    EXPECT_NO_THROW(square.Area());
    EXPECT_NO_THROW(square.GeomCenter());
}

TEST(SquareTest, AreaCalculation) {
    Point<double> p1(0,0), p2(1,0), p3(1,1), p4(0,1);
    Square<double> square(p1, p2, p3, p4);
    EXPECT_NEAR(square.Area(), 1.0, figure::EPS);  
}

TEST(SquareTest, CenterCalculation) {
    Point<double> p1(0,0), p2(2,0), p3(2,2), p4(0,2);
    Square<double> square(p1, p2, p3, p4);
    Point<double> center = square.GeomCenter();
    EXPECT_NEAR(center.x, 1.0, figure::EPS);  
    EXPECT_NEAR(center.y, 1.0, figure::EPS); 
}

TEST(TrapezeTest, DefaultConstructor) {
    Trapeze<double> trapeze;
    EXPECT_NO_THROW(trapeze.Area());
    EXPECT_NO_THROW(trapeze.GeomCenter());
}

TEST(TrapezeTest, AreaCalculation) {
    Point<double> p1(0,0), p2(4,0), p3(3,2), p4(1,2);
    Trapeze<double> trapeze(p1, p2, p3, p4);
    EXPECT_NEAR(trapeze.Area(), 6.0, figure::EPS);  
}

TEST(VectorTest, DefaultConstructor) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    EXPECT_TRUE(vec.IsEmpty());
    EXPECT_EQ(vec.Size(), 0);
}

TEST(VectorTest, PushBack) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    auto rect = std::make_shared<Rectangle<double>>();
    vec.PushBack(std::move(rect));
    EXPECT_EQ(vec.Size(), 1);
}

TEST(VectorTest, Erase) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    auto rect = std::make_shared<Rectangle<double>>();
    vec.PushBack(std::move(rect));
    vec.Erase(0);
    EXPECT_TRUE(vec.IsEmpty());
}

TEST(VectorTest, AccessOperator) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    auto rect = std::make_shared<Rectangle<double>>();
    vec.PushBack(std::move(rect));
    EXPECT_NO_THROW((*vec[0]).Area());
}

TEST(VectorTest, OutOfRangeAccess) {
    Vector<std::shared_ptr<Figure<double>>> vec;
    EXPECT_THROW(vec[0], std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}