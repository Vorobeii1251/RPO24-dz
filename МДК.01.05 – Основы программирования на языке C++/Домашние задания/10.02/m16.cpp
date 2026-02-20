#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool replaceSpacesWithUnderscore(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия входного файла: " << inputFile << std::endl;
        return false;
    }
    
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка создания выходного файла: " << outputFile << std::endl;
        inFile.close();
        return false;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        std::replace(line.begin(), line.end(), ' ', '_');
        outFile << line << '\n';
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << "Файл обработан успешно!" << std::endl;
    return true;
}

bool replaceSpacesInWholeFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия входного файла: " << inputFile << std::endl;
        return false;
    }
    
    std::string content((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());
    inFile.close();
    
    std::replace(content.begin(), content.end(), ' ', '_');
    
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка создания выходного файла: " << outputFile << std::endl;
        return false;
    }
    
    outFile << content;
    outFile.close();
    
    std::cout << "Файл обработан успешно (целиком)!" << std::endl;
    return true;
}

int main() {
    std::ofstream outFile("input.txt");
    outFile << "Это текст с пробелами.\n";
    outFile << "Здесь тоже есть пробелы между словами.\n";
    outFile << "А в этой строке пробелов больше чем слов\n";
    outFile << "Последняя строка файла.\n";
    outFile.close();
    
    std::cout << "Исходный файл:" << std::endl;
    std::ifstream inFile("input.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }
    inFile.close();
    
    replaceSpacesWithUnderscore("input.txt", "output.txt");
    
    std::cout << "\nОбработанный файл:" << std::endl;
    std::ifstream resultFile("output.txt");
    while (std::getline(resultFile, line)) {
        std::cout << line << std::endl;
    }
    resultFile.close();
    
    return 0;
}