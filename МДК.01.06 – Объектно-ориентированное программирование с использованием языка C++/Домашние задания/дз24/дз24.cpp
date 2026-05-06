#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send() = 0; 
};

class EmailNotification : public Notification {
private:
    std::string email;
    std::string subject;
    std::string message;
    
public:
    EmailNotification(const std::string& e, const std::string& subj, const std::string& msg)
        : email(e), subject(subj), message(msg) {}
    
    void send() override {
        std::cout << "📧 Email -> " << email << " | " << subject << " | " << message << std::endl;
    }
};

class SMSNotification : public Notification {
private:
    std::string phone;
    std::string message;
    
public:
    SMSNotification(const std::string& p, const std::string& msg)
        : phone(p), message(msg) {}
    
    void send() override {
        std::cout << "📱 SMS -> " << phone << " | " << message << std::endl;
    }
};

class PushNotification : public Notification {
private:
    std::string deviceToken;
    std::string title;
    std::string body;
    
public:
    PushNotification(const std::string& token, const std::string& t, const std::string& b)
        : deviceToken(token), title(t), body(b) {}
    
    void send() override {
        std::cout << "📲 PUSH -> " << deviceToken << " | " << title << " | " << body << std::endl;
    }
};

void sendAllNotifications(const std::vector<Notification*>& notifications) {
    for (auto* notif : notifications) {
        notif->send();
    }
}

int main() {
    EmailNotification email("user@test.com", "Hello", "Welcome to our service!");
    SMSNotification sms("+79991234567", "Your code is 1234");
    PushNotification push("device_123", "New message", "You have a new notification");
    
    std::cout << "=== Direct calls ===" << std::endl;
    email.send();
    sms.send();
    push.send();
    
    std::cout << "\n=== Polymorphism ===" << std::endl;
    std::vector<Notification*> notifs = {&email, &sms, &push};
    sendAllNotifications(notifs);
    
    std::cout << "\n=== Dynamic creation ===" << std::endl;
    Notification* notif = new PushNotification("new_device", "Alert", "System update available");
    notif->send();
    delete notif;
    
    return 0;
}