#include <iostream>
#include <string_view>
#include <vector>
#include <cctype>

std::vector<std::string_view> split(std::string_view str) {
    std::vector<std::string_view> result;
    
    size_t start = 0;
    size_t end = 0;
    
    while (start < str.length()) {
        while (start < str.length() && std::isspace(str[start])) {
            start++;
        }
        
        if (start >= str.length()) break;
        
        end = start;
        while (end < str.length() && !std::isspace(str[end])) {
            end++;
        }
        
        result.push_back(str.substr(start, end - start));
        
        start = end;
    }
    
    return result;
}

int main() {
    std::string_view text = "Hello world from C++ programming";
    
    auto words = split(text);
    
    std::cout << "Разбиение строки:" << std::endl;
    for (size_t i = 0; i < words.size(); i++) {
        std::cout << i + 1 << ": '" << words[i] << "'" << std::endl;
    }
    
    return 0;
}