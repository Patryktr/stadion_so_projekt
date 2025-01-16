//
// Created by patry on 11.01.2025.
//

#include "Kibic.h"

#include <ctime>
#include <iostream>
#include <unistd.h>
#include <bits/locale_classes.h>



void Kibic::generateRandomData(unsigned int seed) {
    srand(time(nullptr));
    static const string names[] = {
        "Adam", "Ewa", "Marek", "Kasia", "Jan", "Anna", "Tomek", "Agnieszka", "Piotr", "Zosia"
    };
    static string surnames[] = {
        "Kowalski", "Nowak", "Wiśniewski", "Wójcik", "Kowalczyk", "Kamiński", "Lewandowski", "Szymański", "Zieliński",
        "Woźniak"
    };



    this->name = names[rand() % 10];
    this->surname = surnames[rand() % 10];
    this->age = rand() % 100;
    generateRandomClub();
    generateRandomStatus();
}
    void Kibic::generateRandomStatus() {
    int randomValue = rand() % 100; // Losujemy liczbę od 0 do 99
    if (randomValue < 5) {
        this->status = VIP; // 5% szans na VIP
    } else {
        this->status = REGULAR; // 95% szans na Regular
    }
}
void Kibic::generateRandomClub() {
    int randomValue = rand() % 2;
    if (randomValue < 0) {
        this->club = FC_BARCELONA;
    }else {
        this->club=REAL_MADRYT;
    }
}
Kibic::Kibic() {
this->fanPid= fork();


    if (this->fanPid == 0) {

        generateRandomData(rand());
        cout << "Kibic proces (PID: " << getpid() << "): " << name << " " << surname << " (" << getStatusAsString()
             << ", " << getClubAsString() << ")" << endl;
        exit(0); // Zakończenie procesu dziecka
    } else if (fanPid > 0) {
        // Proces rodzica
        cout << "Proces kibica został stworzony (PID: " << fanPid << ")" << endl;
    } else {
        // Błąd w fork()
        cerr << "Błąd tworzenia procesu!" << endl;
    }
    generateRandomData(rand());

}

Kibic::~Kibic() {
}


bool Kibic::isAdult() {
    return this->age >= 18;
}

string Kibic::getName() {
    return this->name;
}

string Kibic::getSurname() {
    return this->surname;
}

unsigned Kibic::getAge() {
    return this->age;
}
Status Kibic::getStatus() {
    return this->status;
}
bool Kibic::isVIP() {
    return this->status==VIP;
}
bool Kibic::isSameClub(Club otherClub) {
    return this->club == otherClub;
}
string Kibic::getClubAsString() {
    switch (club) {
        case FC_BARCELONA: return "F.C Barcelona";
        case REAL_MADRYT: return "Real Madryt";
        default: return "Unknown";
    }
}
string Kibic::getStatusAsString() {
    switch (status) {
        case REGULAR: return "Regular";
        case VIP: return "VIP";
        default: return "Unknown";
    }
}