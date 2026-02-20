
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void task2_compareSorts() {
    std::cout << "\n=== Задание 2: Сравнение sort и пузырька ===\n";
    
    const size_t SMALL_SIZE = 10000;
    const size_t LARGE_SIZE = 100000;
    
    std::vector<int> arrSmall = generateRandomArray(SMALL_SIZE);
    std::vector<int> arrSmallCopy = arrSmall;
    
    double timeBubble = measureTime([](std::vector<int>& v) {
        bubbleSort(v);
    }, arrSmall);
    
    double timeStdSort = measureTime([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    }, arrSmallCopy);
    
    std::cout << "Размер массива: " << SMALL_SIZE << "\n";
    std::cout << "Пузырьковая сортировка: " << timeBubble << " секунд\n";
    std::cout << "std::sort: " << timeStdSort << " секунд\n";
    std::cout << "std::sort быстрее в " << timeBubble / timeStdSort << " раз\n\n";
    
    std::vector<int> arrLarge = generateRandomArray(LARGE_SIZE);
    std::vector<int> arrLargeCopy = arrLarge;
    
    timeStdSort = measureTime([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    }, arrLargeCopy);
    
    std::cout << "Размер массива: " << LARGE_SIZE << "\n";
    std::cout << "std::sort: " << timeStdSort << " секунд\n";
    std::cout << "Пузырек на таком размере будет выполняться очень долго (часы)\n";
}