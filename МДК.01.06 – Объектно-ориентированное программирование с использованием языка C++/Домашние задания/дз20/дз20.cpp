#include <iostream>
#include <string>

class Device {
protected:
    std::string deviceName;
    bool isOn;
    
public:
    Device(const std::string& name = "Unknown") : deviceName(name), isOn(false) {
        std::cout << "Device created: " << deviceName << std::endl;
    }
    
    virtual ~Device() {
        std::cout << "Device destroyed: " << deviceName << std::endl;
    }
    
    virtual void turnOn() {
        isOn = true;
        std::cout << deviceName << " turned ON" << std::endl;
    }
    
    virtual void turnOff() {
        isOn = false;
        std::cout << deviceName << " turned OFF" << std::endl;
    }
    
    virtual void getStatus() const {
        std::cout << deviceName << " is " << (isOn ? "ON" : "OFF") << std::endl;
    }
    
    std::string getName() const { return deviceName; }
    bool isDeviceOn() const { return isOn; }
};

class Light : public Device {
private:
    int brightness;
    
public:
    Light(const std::string& name, int bright = 100) 
        : Device(name), brightness(bright) {
        std::cout << "Light created: " << name << " (brightness: " << brightness << "%)" << std::endl;
    }
    
    void turnOn() override {
        Device::turnOn();
        std::cout << "  -> Light brightness: " << brightness << "%" << std::endl;
    }
    
    void turnOff() override {
        Device::turnOff();
        std::cout << "  -> Light is OFF" << std::endl;
    }
    
    void getStatus() const override {
        Device::getStatus();
        std::cout << "  -> Brightness: " << brightness << "%" << std::endl;
    }
    
    void setBrightness(int level) {
        if (level >= 0 && level <= 100) {
            brightness = level;
            std::cout << "Brightness set to " << brightness << "%" << std::endl;
        }
    }
    
    int getBrightness() const { return brightness; }
};

class Thermostat : private Device {
private:
    double temperature;
    double targetTemp;
    
public:
    Thermostat(const std::string& name, double target = 22.0) 
        : Device(name), temperature(20.0), targetTemp(target) {
        std::cout << "Thermostat created: " << name << " (target: " << targetTemp << "°C)" << std::endl;
    }
    
    void turnOn() {
        Device::turnOn();
        std::cout << "  -> Thermostat target: " << targetTemp << "°C" << std::endl;
    }
    
    void turnOff() {
        Device::turnOff();
        std::cout << "  -> Thermostat is OFF" << std::endl;
    }
    
    void getStatus() const {
        Device::getStatus();
        std::cout << "  -> Current temp: " << temperature << "°C, Target: " << targetTemp << "°C" << std::endl;
    }
    
    void setTargetTemperature(double temp) {
        targetTemp = temp;
        std::cout << "Target temperature set to " << targetTemp << "°C" << std::endl;
    }
    
    void setCurrentTemperature(double temp) {
        temperature = temp;
        std::cout << "Current temperature: " << temperature << "°C" << std::endl;
        
        if (isOn) {
            if (temperature < targetTemp) std::cout << "  -> HEATING ON" << std::endl;
            else if (temperature > targetTemp) std::cout << "  -> COOLING ON" << std::endl;
            else std::cout << "  -> Temperature OK" << std::endl;
        }
    }
    
    void showName() const { std::cout << "Name: " << getName() << std::endl; }
    bool isOn_() const { return isDeviceOn(); }
};

int main() {
    std::cout << "===== SMART HOME SYSTEM =====" << std::endl;
    
    std::cout << "\n--- LIGHT (public inheritance) ---" << std::endl;
    Light lamp("Living Room Lamp", 80);
    lamp.turnOn();      // ✅ доступно
    lamp.setBrightness(50);
    lamp.getStatus();   // ✅ доступно
    lamp.turnOff();     // ✅ доступно
    
    std::cout << "\n--- THERMOSTAT (private inheritance) ---" << std::endl;
    Thermostat thermo("Living Room Thermostat", 22.5);
    
    
    thermo.turnOn();
    thermo.setCurrentTemperature(20.0);
    thermo.setTargetTemperature(23.0);
    thermo.getStatus();
    thermo.turnOff();
    
    thermo.showName();
    std::cout << "Is on: " << (thermo.isOn_() ? "YES" : "NO") << std::endl;
    
    std::cout << "\n--- POLYMORPHISM ---" << std::endl;
    Device* device = new Light("Hall Light", 90);
    device->turnOn();
    device->getStatus();
    delete device;
    
    
    return 0;
}