#include "Stadion.h"

#include <iostream>
#include <stdexcept>
#include <mutex>

Stadion* Stadion::instance = nullptr;
std::mutex Stadion::instanceMutex;

Stadion::Stadion(int maxCapacity)
    : capacity(maxCapacity),
      currentNumberOfFans(0),
      g1(3,"bramka 1"), g2(3,"bramka 2"), g3(3,"bramka 3") {}

Stadion::~Stadion() {}

Stadion* Stadion::getInstance(int maxCapacity) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance) {
        instance = new Stadion(maxCapacity);
    }
    return instance;
}

void Stadion::releaseInstance() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

bool Stadion::hasSpace() const {
    return currentNumberOfFans < capacity;
}

void Stadion::addFan() {
    if (currentNumberOfFans < capacity) {
        currentNumberOfFans++;
    }
}

Gate* Stadion::getGate(int gateNumber) { // Zmieniono na wskaźnik
    switch (gateNumber) {
        case 1: return &g1;
        case 2: return &g2;
        case 3: return &g3;
        default:
            throw std::invalid_argument("Invalid gate number");
    }
}

void Stadion::displayStatus() {
    cout << "\n===== STAN STADIONU =====\n";
    cout << "Aktualna liczba kibiców: " << currentNumberOfFans << "/" << capacity << "\n";
    cout << "Bramki: \n";
    cout << " - " << g1.getName() << "\n";
    cout << " - " << g2.getName() << "\n";
    cout << " - " << g3.getName() << "\n";
    cout << "==========================\n\n";
}
