

// Gate.h - Klasa bramki
#ifndef GATE_H
#define GATE_H
#include "Fan.h"
#include <vector>
#include <semaphore.h>

class Gate {
private:
    int gateCapacity;
    int currentNumberOfFans;
    Club currentClub;
    sem_t gateSemaphore;
    string gateName;

public:
    Gate(int capacity,string gateName);
    ~Gate();
    bool tryEnter(Fan fan);
    void leaveGate(Fan fan);
    bool hasSpaceAndAccepts(Club club) const;
    string getName() const;
};
#endif