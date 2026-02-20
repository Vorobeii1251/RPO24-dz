#include <iostream>
#include <fstream>
#include <string>

size_t countLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 0;
    }
    
    size_t lineCount = 0;
    std::string line;
    
    while (std::getline(file, line)) {
        lineCount++;
    }
    
    file.close();
    return lineCount;
}

size_t countNonEmptyLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 0;
    }
    
    size_t lineCount = 0;
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    
    file.close();
    return lineCount;
}

int main() {
    std::ofstream outFile("test.txt");
    outFile << "Первая строка\n";
    outFile << "Вторая строка\n";
    outFile << "\n";
    outFile << "Третья строка\n";
    outFile << "Четвертая строка\n";
    outFile.close();
    
    std::cout << "Всего строк: " << countLines("test.txt") << std::endl;
    std::cout << "Непустых строк: " << countNonEmptyLines("test.txt") << std::endl;
    
    return 0;
}