#include <iostream>
#include <string>

enum class ClothingCategory {
    TSHIRT, SHIRT, PANTS, JEANS, DRESS, JACKET, COAT, SKIRT, SWEATER, SHOES
};

std::string categoryToString(ClothingCategory category) {
    switch (category) {
        case ClothingCategory::TSHIRT: return "Футболка";
        case ClothingCategory::SHIRT:  return "Рубашка";
        case ClothingCategory::PANTS:  return "Брюки";
        case ClothingCategory::JEANS:  return "Джинсы";
        case ClothingCategory::DRESS:  return "Платье";
        case ClothingCategory::JACKET: return "Куртка";
        case ClothingCategory::COAT:   return "Пальто";
        case ClothingCategory::SKIRT:  return "Юбка";
        case ClothingCategory::SWEATER:return "Свитер";
        case ClothingCategory::SHOES:  return "Обувь";
        default: return "Неизвестно";
    }
}

class Clothes {
private:
    ClothingCategory category;
    std::string fullName;
    double price;
    std::string size;
    std::string color;

public:
    Clothes() : category(ClothingCategory::TSHIRT), fullName("Неизвестно"), 
                price(0.0), size("M"), color("Белый") {}
    
    Clothes(ClothingCategory cat, const std::string& name, double pr, 
            const std::string& sz, const std::string& col) 
        : category(cat), fullName(name), price(pr), size(sz), color(col) {}
    
    std::string getName() const { return fullName; }
    double getPrice() const { return price; }
    ClothingCategory getCategory() const { return category; }
    std::string getCategoryString() const { return categoryToString(category); }
    std::string getSize() const { return size; }
    std::string getColor() const { return color; }
    
    void setName(const std::string& newName) { if (!newName.empty()) fullName = newName; }
    void setPrice(double newPrice) { if (newPrice >= 0) price = newPrice; }
    void setCategory(ClothingCategory newCategory) { category = newCategory; }
    void setSize(const std::string& newSize) { size = newSize; }
    void setColor(const std::string& newColor) { if (!newColor.empty()) color = newColor; }
    
    void display() const {
        std::cout << "\nВид: " << categoryToString(category) 
                  << " | Название: " << fullName 
                  << " | Цена: " << price << " руб."
                  << " | Размер: " << size 
                  << " | Цвет: " << color << std::endl;
    }
};

int main() {
    Clothes tshirt(ClothingCategory::TSHIRT, "Хлопковая футболка", 1999.99, "M", "Синий");
    Clothes jacket(ClothingCategory::JACKET, "Кожаная куртка", 8999.99, "L", "Чёрный");
    
    std::cout << "=== Демонстрация ===" << std::endl;
    
    std::cout << "Название: " << tshirt.getName() << std::endl;
    std::cout << "Цена: " << tshirt.getPrice() << std::endl;
    std::cout << "Категория: " << tshirt.getCategoryString() << std::endl;
    std::cout << "Размер: " << tshirt.getSize() << std::endl;
    std::cout << "Цвет: " << tshirt.getColor() << std::endl;
    
    jacket.setName("Зимняя куртка");
    jacket.setPrice(12999.99);
    jacket.setCategory(ClothingCategory::COAT);
    
    // Вывод информаци
    tshirt.display();
    jacket.display();
    
    return 0;
}