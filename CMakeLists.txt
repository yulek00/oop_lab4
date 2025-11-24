cmake_minimum_required(VERSION 3.10)
project(Figures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)

enable_testing()

find_package(GTest REQUIRED)

add_executable(unit_test tests/unit_test.cpp)
target_link_libraries(unit_test GTest::GTest GTest::Main)

add_test(NAME UnitTests COMMAND unit_test)