#include "Stadion.h"
#include <iostream>
#include <mutex>

Stadion* Stadion::instance = nullptr;
std::mutex Stadion::instanceMutex;

Stadion::Stadion(int maxCapacity, int shmID)
    : capacity(maxCapacity), g1(3, "Bramka 1"), g2(3, "Bramka 2"), g3(3, "Bramka 3") {

    sharedFanCount = (int*)shmat(shmID, NULL, 0);
    if (sharedFanCount == (void*)-1) {
        perror("Błąd przy podłączaniu pamięci współdzielonej");
        exit(1);
    }
    *sharedFanCount = 0;
}

Stadion::~Stadion() {
    shmdt(sharedFanCount);
}

Stadion* Stadion::getInstance(int maxCapacity, int shmID) {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance) {
        instance = new Stadion(maxCapacity, shmID);
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
    return *sharedFanCount < capacity;
}
void Stadion::addFan(Fan fan) {
    if (*sharedFanCount < capacity) {
        (*sharedFanCount)++;
        fan.setStatus(KIBICUJE);
        fanData[fan.fanID] = fan;
        displayStatus();
    }
}


void Stadion::removeFan(int fanID) {
    if (*sharedFanCount > 0 && fanData.find(fanID) != fanData.end()) {
        (*sharedFanCount)--;
        fanData.erase(fanID);
        displayStatus();
    }
}

void Stadion::displayStatus() {
    std::cout << "\n===== STAN STADIONU =====\n";
    std::cout << "Aktualna liczba kibiców: " << *sharedFanCount << "/" << capacity << "\n";
    std::cout << "Bramki: \n";
    std::cout << " - " << g1.getName() << "\n";
    std::cout << " - " << g2.getName() << "\n";
    std::cout << " - " << g3.getName() << "\n";

    std::cout << "Lista kibiców:\n";
    for (const auto& [id, fan] : fanData) {
        std::cout << " - Kibic " << fan.getName()
                  << " (ID: " << id << ", Klub: "
                  << (fan.getClub() == REAL_MADRYT ? "Real Madryt" : "FC Barcelona")
                  << ", Bilet: " << (fan.getTicketType() == VIP ? "VIP" : "Regularny")
                  << ", Status: " << (fan.getStatus() == KIBICUJE ? "Kibicuje" : "Nie przeszedł kontroli")
                  << ")\n";
    }
    std::cout << "==========================\n\n";
}

void Stadion::updateFanStatus(int fanID, FanStatus status) {
    if (fanData.find(fanID) != fanData.end()) {
        fanData[fanID].setStatus(status);
        displayStatus();
    }
}

int Stadion::getCapacity() {
    return capacity;
}
Gate* Stadion::getGate(int gateNumber) {
    switch (gateNumber) {
        case 1: return &g1;
        case 2: return &g2;
        case 3: return &g3;
        default:
            std::cerr << "[ERROR] Niepoprawny numer bramki: " << gateNumber << std::endl;
        return nullptr;
    }
}
int* Stadion::getFanCount() const {
    return sharedFanCount;
}


