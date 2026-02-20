#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

int divideNumbers(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero in low level");
    }
    return a / b;
}

std::vector<int> processValues(const std::vector<int>& values, int divisor) {
    std::vector<int> result;
    for (int val : values) {
        try {
            result.push_back(divideNumbers(val, divisor));
        }
        catch (const std::exception& e) {
            throw std::runtime_error(std::string("Processing failed: ") + e.what());
        }
    }
    return result;
}

void validateAndProcess(const std::vector<int>& data, int divisor) {
    if (data.empty()) {
        throw std::invalid_argument("Input data is empty");
    }
    
    if (divisor < 0) {
        throw std::out_of_range("Divisor cannot be negative");
    }
    
    auto result = processValues(data, divisor);
    
    std::cout << "Processing successful. Results: ";
    for (int r : result) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
}

void runApplication(const std::vector<int>& input, int div) {
    std::cout << "Starting application..." << std::endl;
    
    try {
        validateAndProcess(input, div);
        std::cout << "Application completed successfully" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Validation error: " << e.what() << std::endl;
        throw; 
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Range error: " << e.what() << std::endl;
        throw;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        throw;
    }
}

class Resource {
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "Resource '" << name_ << "' acquired" << std::endl;
    }
    ~Resource() {
        std::cout << "Resource '" << name_ << "' released" << std::endl;
    }
private:
    std::string name_;
};

int main() {
    std::cout << "=== Задание 5: Цепочка вызовов ===\n\n";
    
    {
        std::cout << "Тест 1: Нормальная работа\n";
        Resource res("main_resource");
        
        try {
            std::vector<int> data = {10, 20, 30, 40, 50};
            runApplication(data, 5);
        }
        catch (const std::exception& e) {
            std::cerr << "Main caught: " << e.what() << std::endl;
        }
        std::cout << std::string(50, '-') << "\n\n";
    }
    
    {
        std::cout << "Тест 2: Деление на ноль\n";
        Resource res("main_resource");
        
        try {
            std::vector<int> data = {10, 20, 30, 40, 50};
            runApplication(data, 0); 
        }
        catch (const std::exception& e) {
            std::cerr << "Main caught: " << e.what() << std::endl;
        }
        std::cout << std::string(50, '-') << "\n\n";
    }
    
    {
        std::cout << "Тест 3: Пустой вектор\n";
        Resource res("main_resource");
        
        try {
            std::vector<int> data;
            runApplication(data, 2); 
        }
        catch (const std::exception& e) {
            std::cerr << "Main caught: " << e.what() << std::endl;
        }
        std::cout << std::string(50, '-') << "\n\n";
    }
    
    {
        std::cout << "Тест 4: Отрицательный делитель\n";
        Resource res("main_resource");
        
        try {
            std::vector<int> data = {10, 20, 30};
            runApplication(data, -5); 
        }
        catch (const std::exception& e) {
            std::cerr << "Main caught: " << e.what() << std::endl;
        }
        std::cout << std::string(50, '-') << "\n\n";
    }
    
    std::cout << "Программа завершена" << std::endl;
    return 0;
}