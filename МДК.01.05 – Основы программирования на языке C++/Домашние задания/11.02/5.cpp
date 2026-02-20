template<typename Func>
std::vector<double> multipleMeasurements(Func func, int measurementsCount) {
    std::vector<double> times;
    
    for (int i = 0; i < measurementsCount; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        
        double time = std::chrono::duration<double>(end - start).count();
        times.push_back(time);
    }
    
    return times;
}

void printStatistics(const std::vector<double>& times, const std::string& name) {
    if (times.empty()) return;
    
    double sum = 0;
    double min = times[0];
    double max = times[0];
    
    for (double t : times) {
        sum += t;
        if (t < min) min = t;
        if (t > max) max = t;
    }
    
    double avg = sum / times.size();
    
    std::cout << name << ":\n";
    std::cout << "  Замеры: ";
    for (size_t i = 0; i < times.size(); i++) {
        std::cout << times[i];
        if (i < times.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "  Минимальное: " << min << " секунд\n";
    std::cout << "  Максимальное: " << max << " секунд\n";
    std::cout << "  Среднее: " << avg << " секунд\n\n";
}

void task5_multipleMeasurements() {
    std::cout << "\n=== Задание 5: 5 замеров и среднее время ===\n";
    
    const size_t SIZE = 100000;
    const int MEASUREMENTS = 5;
    
    std::vector<int> baseArr = generateRandomArray(SIZE);
    
    auto sortMeasurements = multipleMeasurements([&]() {
        std::vector<int> arr = baseArr;
        std::sort(arr.begin(), arr.end());
    }, MEASUREMENTS);
    printStatistics(sortMeasurements, "std::sort (5 замеров)");
    
    int target = baseArr[SIZE / 2];
    auto linearMeasurements = multipleMeasurements([&]() {
        linearSearch(baseArr, target);
    }, MEASUREMENTS);
    printStatistics(linearMeasurements, "Линейный поиск (5 замеров)");
    
    std::vector<int> sortedArr = baseArr;
    std::sort(sortedArr.begin(), sortedArr.end());
    
    auto binaryMeasurements = multipleMeasurements([&]() {
        binarySearch(sortedArr, target);
    }, MEASUREMENTS);
    printStatistics(binaryMeasurements, "Бинарный поиск (5 замеров)");
}