#include <iostream>
#include <stdexcept>
#include <string>

class DivisionByZeroException : public std::exception {
private:
    std::string message;
public:
    DivisionByZeroException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};


template<typename T>
T divide(T a, T b) {
    if (b == 0) {
        throw DivisionByZeroException("Деление на ноль в шаблонной функции");
    }
    return a / b;
}

int divideInt(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Делитель не может быть нулем (int)");
    }
    if (a % b != 0) {
        throw std::overflow_error("Результат не целое число");
    }
    return a / b;
}

int main() {
    std::cout << "=== Задание 2: Разные типы исключений ===\n";
    
    try {
        std::cout << "double: " << divide(10.5, 2.0) << std::endl;
        std::cout << "int: " << divideInt(10, 3) << std::endl; 
    }
    catch (const DivisionByZeroException& e) {
        std::cerr << "DivisionByZero: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Overflow: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Other exception: " << e.what() << std::endl;
    }
    
    return 0;
}