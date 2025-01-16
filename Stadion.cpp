//
// Created by patry on 13.01.2025.
//

#include "Stadion.h"

Stadion *Stadion::getInstance(int maxCapacity) {
    if (!instance) {
        instance = new Stadion(maxCapacity);
    }
    return instance;
}

bool Stadion::admitFan() {
    if (this->currentNumberOfFans < this->capacity) {
        this->currentNumberOfFans++;
        return true;
    }
    return false;
}

bool Stadion::removeFan() {
    if (this->currentNumberOfFans>0) {
        currentNumberOfFans--;
        return true;
    }
    return false;
}

void Stadion::clearStadium() {
    this->currentNumberOfFans = 0;
}

int Stadion::getCurrentNumberOfFans() {
    return this->currentNumberOfFans;
}

int Stadion::getCapacity() {
    return this->capacity;
}
