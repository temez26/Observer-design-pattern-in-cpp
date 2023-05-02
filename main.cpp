
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update();
        }
    }
};

class EventDetectorSystem : public Subject {
public:
    void detectEvent() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        notifyObservers();
    }
};

class ConcreteObserver : public Observer {
private:
    int id;
public:
    ConcreteObserver(int id) : id(id) {}

    void update() override {
        std::cout << "Observer " << id << " received update." << std::endl;
    }
};

int main() {
    EventDetectorSystem eventDetectorSystem;
    ConcreteObserver observer1(1);
    ConcreteObserver observer2(2);

    eventDetectorSystem.registerObserver(&observer1);
    eventDetectorSystem.registerObserver(&observer2);

    while (true) {
        eventDetectorSystem.detectEvent();
    }

    return 0;
}
