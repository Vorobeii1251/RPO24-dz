
bool linearSearch(const std::vector<int>& arr, int target) {
    for (int num : arr) {
        if (num == target) return true;
    }
    return false;
}

bool binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

void task3_compareSearch() {
    std::cout << "\n=== Задание 3: Сравнение линейного и бинарного поиска ===\n";
    
    const size_t SIZE = 1000000;
    std::vector<int> arr = generateRandomArray(SIZE);
    
    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());
    
    int target = arr[SIZE / 2];
    
    auto start = std::chrono::high_resolution_clock::now();
    bool found1 = linearSearch(arr, target);
    auto end = std::chrono::high_resolution_clock::now();
    double timeLinear = std::chrono::duration<double>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    bool found2 = binarySearch(sortedArr, target);
    end = std::chrono::high_resolution_clock::now();
    double timeBinary = std::chrono::duration<double>(end - start).count();
    
    std::cout << "Размер массива: " << SIZE << "\n";
    std::cout << "Искомое значение: " << target << "\n";
    std::cout << "Линейный поиск: " << timeLinear << " секунд\n";
    std::cout << "Бинарный поиск: " << timeBinary << " секунд\n";
    std::cout << "Бинарный поиск быстрее в " << timeLinear / timeBinary << " раз\n";
    
    target = -1;
    
    start = std::chrono::high_resolution_clock::now();
    found1 = linearSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    timeLinear = std::chrono::duration<double>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    found2 = binarySearch(sortedArr, target);
    end = std::chrono::high_resolution_clock::now();
    timeBinary = std::chrono::duration<double>(end - start).count();
    
    std::cout << "\nПоиск отсутствующего элемента (-1):\n";
    std::cout << "Линейный поиск: " << timeLinear << " секунд\n";
    std::cout << "Бинарный поиск: " << timeBinary << " секунд\n";
    std::cout << "Бинарный поиск быстрее в " << timeLinear / timeBinary << " раз\n";
}