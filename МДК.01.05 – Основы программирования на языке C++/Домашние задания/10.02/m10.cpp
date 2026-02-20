#include <iostream>
#include <string_view>
#include <cctype>

int sumValues(std::string_view str) {
    int total = 0;
    size_t pos = 0;
    
    while (pos < str.length()) {
        size_t equalsPos = str.find('=', pos);
        if (equalsPos == std::string_view::npos) break;
        
        size_t numStart = equalsPos + 1;
        size_t numEnd = numStart;
        
        while (numEnd < str.length() && std::isdigit(str[numEnd])) {
            numEnd++;
        }
        
        if (numStart < numEnd) {
            int value = 0;
            for (size_t i = numStart; i < numEnd; i++) {
                value = value * 10 + (str[i] - '0');
            }
            total += value;
        }
        
        pos = str.find(';', numEnd);
        if (pos == std::string_view::npos) break;
        pos++;
    }
    
    return total;
}

int sumValuesManual(std::string_view str) {
    int total = 0;
    int currentValue = 0;
    bool readingNumber = false;
    
    for (char c : str) {
        if (std::isdigit(c)) {
            currentValue = currentValue * 10 + (c - '0');
            readingNumber = true;
        } else {
            if (readingNumber) {
                total += currentValue;
                currentValue = 0;
                readingNumber = false;
            }
        }
    }
    
    if (readingNumber) {
        total += currentValue;
    }
    
    return total;
}

int main() {
    std::string_view data = "x=10;y=20;z=30";
    
    std::cout << "Строка: " << data << std::endl;
    std::cout << "Сумма значений: " << sumValues(data) << std::endl;
    std::cout << "Сумма (ручной парсинг): " << sumValuesManual(data) << std::endl;
    
    std::string_view test2 = "a=5;b=15;c=25";
    std::cout << "\nСтрока: " << test2 << std::endl;
    std::cout << "Сумма: " << sumValues(test2) << std::endl;
    
    return 0;
}