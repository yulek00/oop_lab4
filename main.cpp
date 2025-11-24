#include <iostream>
#include <limits>
#include <memory>
#include "vector.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "trapeze.hpp"

int getIntInput(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите целое число." << std::endl;
        } else if (value < minVal || value > maxVal) {
            std::cout << "Ошибка! Число должно быть в диапазоне от " << minVal << " до " << maxVal << "." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

figure::Point<double> getPointInput(int pointNumber) {
    std::cout << "Вершина " << pointNumber << ":" << std::endl;
    double x = getDoubleInput("  x: ");
    double y = getDoubleInput("  y: ");
    return figure::Point<double>(x, y);
}

int main() {
    using FigurePtr = std::shared_ptr<figure::Figure<double>>;
    vector::Vector<FigurePtr> figures;
    int choice = 0;
    
    std::cout << "Программа для работы с фигурами" << std::endl;
    
    do {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Добавить фигуру" << std::endl;
        std::cout << "2. Удалить фигуру по индексу" << std::endl; 
        std::cout << "3. Вывести геометрические центры и площади всех фигур" << std::endl;
        std::cout << "4. Вывести общую площадь всех фигур" << std::endl;
        std::cout << "5. Выйти" << std::endl;
        
        choice = getIntInput("Выберите опцию: ", 1, 5);
        
        switch(choice) {
            case 1: {
                std::cout << "\nВыберите тип фигуры:" << std::endl;
                std::cout << "1 - Прямоугольник" << std::endl;
                std::cout << "2 - Квадрат" << std::endl;
                std::cout << "3 - Трапеция" << std::endl;
                
                int type = getIntInput("Тип фигуры: ", 1, 3);
                
                FigurePtr newFigure = nullptr;
                
                if (type == 1) {
                    std::cout << "\nВведите " << figure::Rectangle<double>::VERTICES_COUNT << " вершины прямоугольника:" << std::endl;
                    figure::Point<double> points[figure::Rectangle<double>::VERTICES_COUNT];
                    for (int i = 0; i < figure::Rectangle<double>::VERTICES_COUNT; ++i) {
                        points[i] = getPointInput(i + 1);
                    }
                    newFigure = std::make_shared<figure::Rectangle<double>>(points[0], points[1], points[2], points[3]);
                    
                } else if (type == 2) {
                    std::cout << "\nВведите " << figure::Square<double>::VERTICES_COUNT << " вершины квадрата:" << std::endl;
                    figure::Point<double> points[figure::Square<double>::VERTICES_COUNT];
                    for (int i = 0; i < figure::Square<double>::VERTICES_COUNT; ++i) {
                        points[i] = getPointInput(i + 1);
                    }
                    newFigure = std::make_shared<figure::Square<double>>(points[0], points[1], points[2], points[3]);
                    
                } else if (type == 3) {
                    std::cout << "\nВведите " << figure::Trapeze<double>::VERTICES_COUNT << " вершины трапеции:" << std::endl;
                    figure::Point<double> points[figure::Trapeze<double>::VERTICES_COUNT];
                    for (int i = 0; i < figure::Trapeze<double>::VERTICES_COUNT; ++i) {
                        points[i] = getPointInput(i + 1);
                    }
                    newFigure = std::make_shared<figure::Trapeze<double>>(points[0], points[1], points[2], points[3]);
                }
                
                figures.PushBack(std::move(newFigure));
                std::cout << "Фигура добавлена!" << std::endl;
                break;
            }
            
            case 2: {
                if (figures.IsEmpty()) {
                    std::cout << "Вектор пуст!" << std::endl;
                    break;
                }
                
                std::cout << "Доступные индексы: 0 - " << figures.Size() - 1 << std::endl;
                int index = getIntInput("Введите индекс для удаления: ", 0, figures.Size() - 1);
                
                figures.Erase(index);
                std::cout << "Фигура с индексом " << index << " удалена." << std::endl;
                break;
            }
            
            case 3: {
                if (figures.IsEmpty()) {
                    std::cout << "Вектор пуст!" << std::endl;
                    break;
                }
                
                std::cout << "Геометрические центры и площади фигур:" << std::endl;
                for (size_t i = 0; i < figures.Size(); ++i) {
                    std::cout << "Фигура " << i << ": ";
                    std::cout << "Центр = " << figures[i]->GeomCenter();
                    std::cout << ", Площадь = " << figures[i]->Area() << std::endl;
                }
                break;
            }
            
            case 4: {
                if (figures.IsEmpty()) {
                    std::cout << "Вектор пуст!" << std::endl;
                    break;
                }
                
                double total = 0.0;
                for (size_t i = 0; i < figures.Size(); ++i) {
                    total += static_cast<double>(*figures[i]);
                }
                std::cout << "Общая площадь всех фигур: " << total << std::endl;
                break;
            }
            
            case 5:
                std::cout << "Выход из программы." << std::endl;
                break;
        }
        
    } while (choice != 5);
    
    return 0;
}