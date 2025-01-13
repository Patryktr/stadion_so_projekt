//
// Created by patry on 11.01.2025.
//

#include "kibic.h"

#include <ctime>
#include <iostream>
#include <bits/locale_classes.h>

void kibic::generateRandomData(unsigned int seed) {
    srand(time(nullptr));
    static const string names[]={"Adam", "Ewa", "Marek", "Kasia", "Jan", "Anna", "Tomek", "Agnieszka", "Piotr", "Zosia"};
    static string surnames[]={"Kowalski", "Nowak", "Wiśniewski", "Wójcik", "Kowalczyk", "Kamiński", "Lewandowski", "Szymański", "Zieliński", "Woźniak"};
    this->name =names[rand()%10];
    this->surname =surnames[rand()%10];
    this->age =rand()%100;
}

kibic::kibic() {
    generateRandomData(rand());//generujemu randomowe dane do obiektu kibic
    worker = thread(&kibic::worker, this); // uruchamiamy wątek
}

kibic::~kibic() {
    if (worker.joinable()) {
        worker.join();

    }
}


bool kibic::isAdult() {
    return this->age>=18;
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
