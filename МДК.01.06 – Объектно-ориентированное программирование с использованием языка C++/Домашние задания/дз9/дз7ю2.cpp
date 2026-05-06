#include <iostream>

class MathUtils {
private:
    MathUtils() = delete;

public:
    static int add(int a, int b) {
        return a + b;
    }
    
    static int sub(int a, int b) {
        return a - b;
    }
    
    static int mul(int a, int b) {
        return a * b;
    }
};

int main() {
    int x = 15, y = 7;
    
    std::cout << "MathUtils::add(" << x << ", " << y << ") = " << MathUtils::add(x, y) << std::endl;
    std::cout << "MathUtils::sub(" << x << ", " << y << ") = " << MathUtils::sub(x, y) << std::endl;
    std::cout << "MathUtils::mul(" << x << ", " << y << ") = " << MathUtils::mul(x, y) << std::endl;
    
    return 0;
}