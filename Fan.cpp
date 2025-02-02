//
// Created by patryk on 1/21/25.
//

#include "Fan.h"

#include <iostream>
#include <random>
#include <unistd.h>
static const string names[] = {
    "Adam", "Ewa", "Marek", "Kasia", "Jan", "Anna", "Tomek", "Agnieszka", "Piotr", "Zosia"
};

void Fan::generateRandomSFan() {
    static constexpr size_t nameCount = sizeof(names) / sizeof(names[0]);

    static random_device rd;
    static mt19937 gen(rd());


    uniform_int_distribution<> nameDist(0, nameCount - 1);
    this->name = names[nameDist(gen)];


    uniform_int_distribution<> ageDist(15, 60);
    this->age = ageDist(gen);

    uniform_int_distribution<> gateDist(1, 3);
    this->gate = gateDist(gen);


    uniform_int_distribution<> clubDist(0, 1);
    this->club = static_cast<Club>(clubDist(gen));


    //losowanie statusu vip 1%
    uniform_int_distribution<> statusDist(0, 99);
    if (statusDist(gen) < 1) {
        // 5% szans na VIP
        this->status = VIP;
    } else {
        // 95% szans na Regular
        this->status = REGULAR;
    }
}

Fan::Fan() {
    this->fanPid = fork();
    generateRandomSFan();
    if (this->fanPid == 0) {
        // Proces potomny


        exit(0);

    } else if (fanPid > 0) {
        // Proces macierzysty
    } else {
        // Błąd tworzenia procesu
        std::cerr << "Błąd tworzenia procesu!" << std::endl;
    }
}

unsigned int Fan::getGate() {
    return this->gate;
}

unsigned int Fan::getAge() {
    return this->age;
}

Club Fan::getClub() {
    return this->club;
}

pid_t Fan::getFanPid() {
    return this->fanPid;
}

string Fan::getName() {
    return this->name;
}

int Fan::getPassCount() const {
    return this->passCount;
}

void Fan::incrementPassCount() {
    this->passCount++;
}

void Fan::resetPassCount() {
    this->passCount = 0;
}
