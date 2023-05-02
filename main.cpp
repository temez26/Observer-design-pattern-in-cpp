
/*
 * To compile this code, use a C++ compiler such as g++:
 * g++ -o observer observer.cpp
 *
 * To run the compiled application:
 * ./observer
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Observer interface
class Observer {
public:
    virtual void update() = 0;
};

// Subject class
class Subject {
private:
    std::vector<Observer*> observers; // list of observers
public:
    // register an observer
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    // notify all observers
    void notifyObservers() {
        for (auto observer : observers) {
            observer->update();
        }
    }
};

// EventDetectorSystem class extends Subject
class EventDetectorSystem : public Subject {
public:
    // simulate event detection and notify observers
    void detectEvent() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Event occurred: one second elapsed." << std::endl;
        notifyObservers();
    }
};

// ConcreteObserver class extends Observer
class ConcreteObserver : public Observer {
private:
    int id; // observer id
public:
    ConcreteObserver(int id) : id(id) {}

    // receive update notification
    void update() override {
        std::cout << "Observer " << id << " received update." << std::endl;
    }
};

int main() {
    EventDetectorSystem eventDetectorSystem;
    ConcreteObserver observer1(1);
    ConcreteObserver observer2(2);

    // register observers
    eventDetectorSystem.registerObserver(&observer1);
    eventDetectorSystem.registerObserver(&observer2);

    // simulate event detection in a loop
    while (true) {
        eventDetectorSystem.detectEvent();
    }

    return 0;
}
