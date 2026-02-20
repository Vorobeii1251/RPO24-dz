long long factorialRecursive(int n) {
    if (n <= 1) return 1;
    return n * factorialRecursive(n - 1);
}

long long factorialIterative(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

long long fibonacciIterative(int n) {
    if (n <= 1) return n;
    
    long long prev = 0;
    long long curr = 1;
    
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

void task4_compareRecursiveIterative() {
    std::cout << "\n=== Задание 4: Сравнение рекурсивной и итеративной функций ===\n";
    
    const int FACT_N = 20;
    
    auto start = std::chrono::high_resolution_clock::now();
    long long factRec = factorialRecursive(FACT_N);
    auto end = std::chrono::high_resolution_clock::now();
    double timeFactRec = std::chrono::duration<double>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    long long factIter = factorialIterative(FACT_N);
    end = std::chrono::high_resolution_clock::now();
    double timeFactIter = std::chrono::duration<double>(end - start).count();
    
    std::cout << "Факториал " << FACT_N << ":\n";
    std::cout << "Рекурсивно: " << factRec << ", время: " << timeFactRec << " секунд\n";
    std::cout << "Итеративно: " << factIter << ", время: " << timeFactIter << " секунд\n";
    std::cout << "Разница: " << timeFactRec / timeFactIter << " раз\n\n";
    
    const int FIB_N = 40; 
    
    start = std::chrono::high_resolution_clock::now();
    long long fibRec = fibonacciRecursive(FIB_N);
    end = std::chrono::high_resolution_clock::now();
    double timeFibRec = std::chrono::duration<double>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    long long fibIter = fibonacciIterative(FIB_N);
    end = std::chrono::high_resolution_clock::now();
    double timeFibIter = std::chrono::duration<double>(end - start).count();
    
    std::cout << "Число Фибоначчи " << FIB_N << ":\n";
    std::cout << "Рекурсивно: " << fibRec << ", время: " << timeFibRec << " секунд\n";
    std::cout << "Итеративно: " << fibIter << ", время: " << timeFibIter << " секунд\n";
    std::cout << "Итеративный быстрее в " << timeFibRec / timeFibIter << " раз\n";
}