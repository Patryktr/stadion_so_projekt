//
// Created by patry on 11.01.2025.
//

#include "kibic.h"

#include <ctime>
#include <iostream>
#include <unistd.h>
#include <bits/locale_classes.h>



void kibic::generateRandomData(unsigned int seed) {
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
    void kibic::generateRandomStatus() {
    int randomValue = rand() % 100; // Losujemy liczbę od 0 do 99
    if (randomValue < 5) {
        this->status = VIP; // 5% szans na VIP
    } else {
        this->status = REGULAR; // 95% szans na Regular
    }
}
void kibic::generateRandomClub() {
    int randomValue = rand() % 2;
    if (randomValue < 0) {
        this->club = FC_BARCELONA;
    }else {
        this->club=REAL_MADRYT;
    }
}
kibic::kibic() {
fanPid= fork();


    if (fanPid == 0) {
        // Proces dziecka (kibic)
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

kibic::~kibic() {
}


bool kibic::isAdult() {
    return this->age >= 18;
}

string kibic::getName() {
    return this->name;
}

string kibic::getSurname() {
    return this->surname;
}

unsigned kibic::getAge() {
    return this->age;
}
Status kibic::getStatus() {
    return this->status;
}
bool kibic::isVIP() {
    return this->status==VIP;
}
bool kibic::isSameClub(Club otherClub) {
    return this->club == otherClub;
}
string kibic::getClubAsString() {
    switch (club) {
        case FC_BARCELONA: return "F.C Barcelona";
        case REAL_MADRYT: return "Real Madryt";
        default: return "Unknown";
    }
}
string kibic::getStatusAsString() {
    switch (status) {
        case REGULAR: return "Regular";
        case VIP: return "VIP";
        default: return "Unknown";
    }
}