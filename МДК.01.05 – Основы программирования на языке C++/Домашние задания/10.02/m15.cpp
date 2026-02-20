#include <iostream>
#include <fstream>
#include <string>

bool copyFile(const std::string& sourceFile, const std::string& destFile) {
    std::ifstream src(sourceFile, std::ios::binary);
    if (!src.is_open()) {
        std::cerr << "Ошибка открытия исходного файла: " << sourceFile << std::endl;
        return false;
    }
    
    std::ofstream dst(destFile, std::ios::binary);
    if (!dst.is_open()) {
        std::cerr << "Ошибка создания файла назначения: " << destFile << std::endl;
        src.close();
        return false;
    }
    
    dst << src.rdbuf();
    
    src.close();
    dst.close();
    
    std::cout << "Файл успешно скопирован!" << std::endl;
    return true;
}

bool copyFileWithBuffer(const std::string& sourceFile, const std::string& destFile) {
    std::ifstream src(sourceFile, std::ios::binary);
    if (!src.is_open()) {
        std::cerr << "Ошибка открытия исходного файла: " << sourceFile << std::endl;
        return false;
    }
    
    std::ofstream dst(destFile, std::ios::binary);
    if (!dst.is_open()) {
        std::cerr << "Ошибка создания файла назначения: " << destFile << std::endl;
        src.close();
        return false;
    }
    
    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    
    while (src.read(buffer, BUFFER_SIZE)) {
        dst.write(buffer, src.gcount());
    }
    dst.write(buffer, src.gcount());
    
    src.close();
    dst.close();
    
    std::cout << "Файл успешно скопирован (с буфером)!" << std::endl;
    return true;
}

int main() {
    std::ofstream outFile("source.txt");
    outFile << "Это содержимое исходного файла.\n";
    outFile << "Оно будет скопировано в другой файл.\n";
    outFile << "Строка 3\nСтрока 4\n";
    outFile.close();
    
    if (copyFile("source.txt", "destination.txt")) {
        std::cout << "\nСодержимое скопированного файла:" << std::endl;
        std::ifstream inFile("destination.txt");
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
    
    return 0;
}