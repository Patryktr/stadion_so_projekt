#ifndef STADION_H
#define STADION_H

#include "Gate.h"
#include "Fan.h"
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <sys/ipc.h>
#include <sys/shm.h>

class Stadion {
private:
    int capacity;
    int* sharedFanCount;
    std::map<int, Fan> fanData; // Pełne dane kibiców
    Gate g1, g2, g3;
    static Stadion* instance;
    static std::mutex instanceMutex;

    Stadion(int maxCapacity, int shmID);
    ~Stadion();

public:
    static Stadion* getInstance(int maxCapacity, int shmID);
    static void releaseInstance();
    bool hasSpace() const;
    void addFan(Fan fan);
    void removeFan(int fanID);
    void displayStatus();
    Gate* getGate(int gateNumber);
    void updateFanStatus(int fanID, FanStatus status);
    int* getFanCount() const;
    int getCapacity();
};

#endif // STADION_H
