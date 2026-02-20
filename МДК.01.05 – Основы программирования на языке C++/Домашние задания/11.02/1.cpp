#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

std::vector<int> generateRandomArray(size_t size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    
    for (auto& num : arr) {
        num = dist(gen);
    }
    return arr;
}

template<typename Func>
double measureTime(Func sortFunc, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

void task1_sort100k() {
    const size_t SIZE = 100000;
    
    std::cout << "=== Задание 1: Сортировка " << SIZE << " элементов ===\n";
    
    std::vector<int> arr = generateRandomArray(SIZE);
    
    std::vector<int> arr1 = arr;
    
    double time = measureTime([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    }, arr1);
    
    std::cout << "std::sort: " << time << " секунд\n";
}