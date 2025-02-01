#ifndef STADION_H
#define STADION_H
#include "Gate.h"
#include <vector>
#include <mutex>

class Stadion {
private:
    int capacity;
    int currentNumberOfFans;
    Gate g1, g2, g3;
    static Stadion* instance;
    static mutex instanceMutex;

    Stadion(int maxCapacity);
    ~Stadion();

public:
    static Stadion* getInstance(int maxCapacity);
    static void releaseInstance();
    bool hasSpace() const;
    void addFan();
    void displayStatus();
    Gate* getGate(int gateNumber);
};

#endif // STADION_H