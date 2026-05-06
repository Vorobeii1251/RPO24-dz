#include <iostream>
#include <string>

class Character {
protected:
    std::string name;
    int health;
    int level;
    
public:
    Character(const std::string& name, int health, int level)
        : name(name), health(health), level(level) {
        std::cout << "[Character] " << name << " создан!" << std::endl;
    }
    
    virtual ~Character() {
        std::cout << "[Character] " << name << " удалён!" << std::endl;
    }
    
    virtual void attack() const {
        std::cout << name << " наносит базовую атаку!" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << name << " (Lvl " << level << ", HP " << health << ")";
    }
    
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getLevel() const { return level; }
    void setHealth(int h) { health = h > 0 ? h : 0; }
};

class Warrior : public Character {
private:
    int rage;
    std::string weapon;
    
public:
    Warrior(const std::string& name, int health, int level, int rage, const std::string& weapon)
        : Character(name, health, level), rage(rage), weapon(weapon) {
        std::cout << "[Warrior] " << name << " вооружился " << weapon << std::endl;
    }
    
    void attack() const override {
        std::cout << "\n⚔️ " << name << " атакует " << weapon << "! (Ярость: " << rage << "%)";
        if (rage >= 70) std::cout << " КРИТИЧЕСКИЙ УДАР!";
        std::cout << std::endl;
    }
    
    void slash() const {
        std::cout << "🌀 " << name << " использует РАЗРУБАЮЩИЙ УДАР " << weapon << "!";
        if (rage >= 50) std::cout << " Расход ярости: 30";
        std::cout << std::endl;
    }
    
    void displayInfo() const override {
        Character::displayInfo();
        std::cout << " | Оружие: " << weapon << " | Ярость: " << rage << "%" << std::endl;
    }
};

class Mage : public Character {
private:
    int mana;
    std::string spell;
    
public:
    Mage(const std::string& name, int health, int level, int mana, const std::string& spell)
        : Character(name, health, level), mana(mana), spell(spell) {
        std::cout << "[Mage] " << name << " выучил заклинание " << spell << std::endl;
    }
    
    void attack() const override {
        std::cout << "\n🔮 " << name << " атакует магией! (Мана: " << mana << "%)";
        if (mana >= 80) std::cout << " УСИЛЕННАЯ МАГИЯ!";
        std::cout << std::endl;
    }
    
    void castSpell() const {
        std::cout << "📜 " << name << " произносит \"" << spell << "\"!";
        if (mana >= 40) {
            std::cout << " Заклинание активировано!";
            if (spell == "Огненный шар") std::cout << " 🔥 50 урона!";
            else if (spell == "Молния") std::cout << " ⚡ 45 урона!";
            else if (spell == "Ледяная стрела") std::cout << " ❄️ Заморозка!";
        } else {
            std::cout << " Недостаточно маны!";
        }
        std::cout << std::endl;
    }
    
    void displayInfo() const override {
        Character::displayInfo();
        std::cout << " | Заклинание: " << spell << " | Мана: " << mana << "%" << std::endl;
    }
};

int main() {
    std::cout << "===== GAME CHARACTER SYSTEM =====" << std::endl;
    
    std::cout << "\n--- Creating Characters ---" << std::endl;
    Warrior warrior("Артур", 250, 10, 85, "Экскалибур");
    Mage mage("Мерлин", 180, 10, 90, "Огненный шар");
    
    std::cout << "\n--- Overridden attack() ---" << std::endl;
    warrior.attack();
    mage.attack();
    
    std::cout << "\n--- Unique Methods ---" << std::endl;
    warrior.slash();
    mage.castSpell();
    
    std::cout << "\n--- Character Info ---" << std::endl;
    warrior.displayInfo();
    mage.displayInfo();
    
    std::cout << "\n--- Polymorphism ---" << std::endl;
    Character* characters[] = {&warrior, &mage};
    for (auto* c : characters) {
        c->attack();
    }
    
    return 0;
}