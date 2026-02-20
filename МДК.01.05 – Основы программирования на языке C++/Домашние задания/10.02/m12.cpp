#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

double averageFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 0.0;
    }
    
    std::vector<double> numbers;
    double num;
    
    while (file >> num) {
        numbers.push_back(num);
    }
    
    file.close();
    
    if (numbers.empty()) {
        std::cout << "Файл пуст или не содержит чисел" << std::endl;
        return 0.0;
    }
    
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    return sum / numbers.size();
}

double averageFromFileStream(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return 0.0;
    }
    
    double sum = 0.0;
    double num;
    int count = 0;
    
    while (file >> num) {
        sum += num;
        count++;
    }
    
    file.close();
    
    if (count == 0) {
        std::cout << "Файл пуст или не содержит чисел" << std::endl;
        return 0.0;
    }
    
    return sum / count;
}

int main() {
    std::ofstream outFile("numbers.txt");
    outFile << "10 20 30 40 50\n60 70 80 90 100\n";
    outFile.close();
    
    double avg = averageFromFile("numbers.txt");
    std::cout << "Среднее значение: " << avg << std::endl;
    
    avg = averageFromFileStream("numbers.txt");
    std::cout << "Среднее (потоковый метод): " << avg << std::endl;
    
    return 0;
}