#include <iostream>
#include <string>

class Product {
private:
    std::string name;
    double price;
    static int productCount;

public:
    Product() : name("Unknown"), price(0.0) {
        productCount++;
        std::cout << "Создан продукт по умолчанию. Всего: " << productCount << std::endl;
    }
    
    Product(const std::string& name, double price) : name(name), price(price) {
        productCount++;
        std::cout << "Создан продукт \"" << name << "\". Всего: " << productCount << std::endl;
    }
    
    Product(const Product& other) : name(other.name), price(other.price) {
        productCount++;
        std::cout << "Создана копия \"" << name << "\". Всего: " << productCount << std::endl;
    }
    
    ~Product() {
        productCount--;
        std::cout << "Удалён \"" << name << "\". Осталось: " << productCount << std::endl;
    }
    
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    
    void setName(const std::string& newName) { name = newName; }
    void setPrice(double newPrice) { if (newPrice >= 0) price = newPrice; }
    
    static int getProductCount() { return productCount; }
    
    void display() const {
        std::cout << "Продукт: " << name << " | Цена: " << price << " руб." << std::endl;
    }
};

int Product::productCount = 0;

int main() {
    std::cout << "Начало: продуктов = " << Product::getProductCount() << std::endl;
    
    Product p1("Книга", 500);
    Product p2("Ручка", 50);
    
    std::cout << "\nВсего продуктов: " << Product::getProductCount() << std::endl;
    
    p1.display();
    p2.display();
    
    return 0;
}