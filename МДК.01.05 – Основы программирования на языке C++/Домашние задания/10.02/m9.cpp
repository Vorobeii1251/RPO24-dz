#include <iostream>
#include <string_view>
#include <cctype>

bool isPalindrome(std::string_view str) {
    if (str.empty()) return true;
    
    size_t left = 0;
    size_t right = str.length() - 1;
    
    while (left < right) {
        while (left < right && !std::isalnum(str[left])) {
            left++;
        }
        while (left < right && !std::isalnum(str[right])) {
            right--;
        }
        
        if (std::tolower(str[left]) != std::tolower(str[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

int main() {
    std::string_view test1 = "A man a plan a canal Panama";
    std::string_view test2 = "race a car";
    std::string_view test3 = "Was it a car or a cat I saw";
    std::string_view test4 = "hello";
    
    std::cout << "'" << test1 << "' - " 
              << (isPalindrome(test1) ? "палиндром" : "не палиндром") << std::endl;
    std::cout << "'" << test2 << "' - " 
              << (isPalindrome(test2) ? "палиндром" : "не палиндром") << std::endl;
    std::cout << "'" << test3 << "' - " 
              << (isPalindrome(test3) ? "палиндром" : "не палиндром") << std::endl;
    std::cout << "'" << test4 << "' - " 
              << (isPalindrome(test4) ? "палиндром" : "не палиндром") << std::endl;
    
    return 0;
}