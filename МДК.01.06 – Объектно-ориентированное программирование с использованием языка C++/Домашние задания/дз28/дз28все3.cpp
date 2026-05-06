#include <iostream>
#include <memory>
#include <string>

// 1
void task1() {
    
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    std::cout << "Значение: " << *ptr << std::endl;
}

//2
void task2() {
    
    std::shared_ptr<int> p1 = std::make_shared<int>(99);
    std::shared_ptr<int> p2 = p1;
    
    std::cout << "Значение: " << *p1 << std::endl;
    std::cout << "use_count(): " << p1.use_count() << std::endl;
}

// 3
class ProblemA;
class ProblemB;

class ProblemA {
public:
    std::shared_ptr<ProblemB> b;
    ~ProblemA() { std::cout << "~ProblemA" << std::endl; }
};

class ProblemB {
public:
    std::shared_ptr<ProblemA> a;
    ~ProblemB() { std::cout << "~ProblemB" << std::endl; }
};

class FixedA;
class FixedB;

class FixedA {
public:
    std::shared_ptr<FixedB> b;
    ~FixedA() { std::cout << "~FixedA" << std::endl; }
};

class FixedB {
public:
    std::weak_ptr<FixedA> a;  // weak_ptr разрывает цикл
    ~FixedB() { std::cout << "~FixedB" << std::endl; }
};

void task3_problem() {
    std::cout << "\n--- ПРОБЛЕМА (утечка памяти) ---" << std::endl;
    auto a = std::make_shared<ProblemA>();
    auto b = std::make_shared<ProblemB>();
    a->b = b;
    b->a = a;
}

void task3_fixed() {
    std::cout << "\n--- РЕШЕНИЕ (weak_ptr) ---" << std::endl;
    auto a = std::make_shared<FixedA>();
    auto b = std::make_shared<FixedB>();
    a->b = b;
    b->a = a;
}

int main() {
    task1();
    task2();
    
    task3_problem();
    task3_fixed();
    
    return 0;
}