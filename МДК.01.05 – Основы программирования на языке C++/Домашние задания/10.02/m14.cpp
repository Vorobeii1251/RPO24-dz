#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct LongestLineInfo {
    std::string line;
    size_t length;
    size_t lineNumber;
};

LongestLineInfo findLongestLine(const std::string& filename) {
    std::ifstream file(filename);
    LongestLineInfo result = {"", 0, 0};
    
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return result;
    }
    
    std::string line;
    size_t currentLine = 0;
    
    while (std::getline(file, line)) {
        currentLine++;
        if (line.length() > result.length) {
            result.length = line.length();
            result.line = line;
            result.lineNumber = currentLine;
        }
    }
    
    file.close();
    return result;
}

size_t findLongestLineLength(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 0;
    }
    
    size_t maxLength = 0;
    std::string line;
    
    while (std::getline(file, line)) {
        maxLength = std::max(maxLength, line.length());
    }
    
    file.close();
    return maxLength;
}

int main() {
    std::ofstream outFile("lines.txt");
    outFile << "Короткая строка\n";
    outFile << "Эта строка немного длиннее предыдущей\n";
    outFile << "Самая длинная строка в этом файле содержит больше символов, чем все остальные\n";
    outFile << "Еще одна строка\n";
    outFile.close();
    
    auto longest = findLongestLine("lines.txt");
    std::cout << "Самая длинная строка:" << std::endl;
    std::cout << "Строка #" << longest.lineNumber << ": '" << longest.line << "'" << std::endl;
    std::cout << "Длина: " << longest.length << " символов" << std::endl;
    
    std::cout << "\nМаксимальная длина (без сохранения): " 
              << findLongestLineLength("lines.txt") << std::endl;
    
    return 0;
}