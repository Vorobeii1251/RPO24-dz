#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int findElementBad(const std::vector<int>& vec, int value, size_t& index) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == value) {
            index = i;
            return 0; 
        }
    }
    return -1; 
}

size_t findElementGood(const std::vector<int>& vec, int value) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == value) {
            return i;
        }
    }
    throw std::runtime_error("Элемент не найден");
}

class Calculator {
public:
    int divideBad(int a, int b) {
        if (b == 0) return -1;
        return a / b;
    }
    
    int divideGood(int a, int b) {
        if (b == 0) throw std::invalid_argument("Деление на ноль");
        return a / b;
    }
    
    int sqrtBad(int x, bool& success) {
        if (x < 0) {
            success = false;
            return 0;
        }
        success = true;
        return x * x;
    }
    
    int sqrtGood(int x) {
        if (x < 0) throw std::domain_error("Корень из отрицательного числа");
        return x * x;
    }
};

int main() {
    std::cout << "=== Задание 4: Замена return-кодов на throw ===\n";
    
    std::vector<int> vec = {10, 20, 30, 40, 50};
    
    size_t index;
    int result = findElementBad(vec, 30, index);
    if (result == 0) {
        std::cout << "Найден на позиции " << index << std::endl;
    } else {
        std::cout << "Не найден" << std::endl;
    }
    
    try {
        size_t pos = findElementGood(vec, 100);
        std::cout << "Найден на позиции " << pos << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    Calculator calc;
    
    try {
        std::cout << "10 / 2 = " << calc.divideGood(10, 2) << std::endl;
        std::cout << "10 / 0 = " << calc.divideGood(10, 0) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка калькулятора: " << e.what() << std::endl;
    }
    
    return 0;
}