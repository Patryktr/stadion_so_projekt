#ifndef STADION_H
#define STADION_H

#include "Gate.h"
#include <vector>
#include <mutex>
#include <sys/ipc.h>
#include <sys/shm.h>

class Stadion {
private:
    int capacity;
    int* sharedFanCount; // Teraz liczba kibiców będzie współdzielona między procesami
    Gate g1, g2, g3;
    static Stadion* instance;
    static std::mutex instanceMutex;

    Stadion(int maxCapacity, int shmID);
    ~Stadion();

public:
    static Stadion* getInstance(int maxCapacity, int shmID);
    static void releaseInstance();
    bool hasSpace() const;
    void addFan();
    void displayStatus();
    Gate* getGate(int gateNumber);
    int getCapacity() const;
};

#endif // STADION_H
