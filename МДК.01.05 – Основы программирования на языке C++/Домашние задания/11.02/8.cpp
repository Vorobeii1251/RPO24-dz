#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

class FileException : public std::runtime_error {
public:
    FileException(const std::string& msg) : std::runtime_error(msg) {}
};

std::vector<std::string> readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw FileException("Не удалось открыть файл: " + filename);
    }
    
    std::string line;
    int lineNumber = 0;
    
    try {
        while (std::getline(file, line)) {
            lineNumber++;
            if (line.length() > 1000) {
                throw FileException("Слишком длинная строка #" + std::to_string(lineNumber));
            }
            lines.push_back(line);
        }
    }
    catch (const std::exception& e) {
        file.close();
        throw; 
    }
    
    if (file.bad()) {
        throw FileException("Ошибка чтения файла");
    }
    
    file.close();
    
    if (lines.empty()) {
        throw FileException("Файл пуст");
    }
    
    return lines;
}

void processFileContent(const std::string& filename) {
    try {
        auto content = readFile(filename);
        std::cout << "Файл прочитан успешно. Строк: " << content.size() << std::endl;
        
        for (size_t i = 0; i < std::min(content.size(), size_t(5)); i++) {
            std::cout << "  " << i+1 << ": " << content[i] << std::endl;
        }
    }
    catch (const FileException& e) {
        std::cerr << "Ошибка файла: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Задание 3: Чтение файла с обработкой ошибок ===\n";
    
    std::ofstream out("test.txt");
    out << "Первая строка\n";
    out << "Вторая строка\n";
    out << "Третья строка\n";
    out.close();
    
    processFileContent("test.txt");
    
    processFileContent("nonexistent.txt");
    
    return 0;
}