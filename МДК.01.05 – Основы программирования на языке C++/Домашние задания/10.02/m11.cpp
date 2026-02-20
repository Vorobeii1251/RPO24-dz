#include <iostream>
#include <string_view>
#include <vector>
#include <cctype>

std::string_view findLongestWord(std::string_view str) {
    std::string_view longestWord;
    size_t maxLength = 0;
    
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
        
        size_t wordLength = end - start;
        if (wordLength > maxLength) {
            maxLength = wordLength;
            longestWord = str.substr(start, wordLength);
        }
        
        start = end;
    }
    
    return longestWord;
}

struct WordInfo {
    std::string_view word;
    size_t position;
    size_t length;
};

WordInfo findLongestWordInfo(std::string_view str) {
    WordInfo result = {std::string_view(), 0, 0};
    
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
        
        size_t wordLength = end - start;
        if (wordLength > result.length) {
            result.length = wordLength;
            result.position = start;
            result.word = str.substr(start, wordLength);
        }
        
        start = end;
    }
    
    return result;
}

int main() {
    std::string_view text = "The quick brown fox jumps over the lazy elephant";
    
    std::string_view longest = findLongestWord(text);
    std::cout << "Строка: " << text << std::endl;
    std::cout << "Самое длинное слово: '" << longest << "'" << std::endl;
    std::cout << "Длина: " << longest.length() << " символов" << std::endl;
    
    auto info = findLongestWordInfo(text);
    std::cout << "\nДетальная информация:" << std::endl;
    std::cout << "Слово: '" << info.word << "'" << std::endl;
    std::cout << "Позиция: " << info.position << std::endl;
    std::cout << "Длина: " << info.length << std::endl;
    
    std::vector<std::string_view> tests = {
        "One two three four",
        "Short and long words here",
        "Single",
        "   Multiple   spaces   test   "
    };
    
    std::cout << "\n--- Тесты ---" << std::endl;
    for (auto test : tests) {
        std::cout << "'" << test << "' -> '"
                  << findLongestWord(test) << "'" << std::endl;
    }
    
    return 0;
}