#include <iostream>
#include <string_view>
#include <cctype>

size_t countWords(std::string_view str) {
    size_t count = 0;
    bool inWord = false;
    
    for (char c : str) {
        if (std::isspace(c)) {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            count++;
        }
    }
    
    return count;
}

int main() {
    std::string_view text = "Hello world from C++";
    std::cout << "Количество слов: " << countWords(text) << std::endl; // 4
    
    text = "   Multiple   spaces   between   ";
    std::cout << "Количество слов: " << countWords(text) << std::endl; // 3
    
    return 0;
}