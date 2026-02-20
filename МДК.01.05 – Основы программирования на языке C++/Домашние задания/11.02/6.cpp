#include <iostream>
#include <stdexcept>

double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Ошибка: деление на ноль!");
    }
    return a / b;
}

int main() {
    try {
        std::cout << "10 / 2 = " << divide(10, 2) << std::endl;
        std::cout << "5 / 0 = " << divide(5, 0) << std::endl;
        std::cout << "Это не выполнится" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Поймано исключение: " << e.what() << std::endl;
    }
    
    std::cout << "Программа продолжает работу" << std::endl;
    return 0;
}