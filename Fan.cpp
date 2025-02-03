#include "Fan.h"

#include <cstring>
#include <random>

static const std::string names[] = {
    "Adam", "Ewa", "Marek", "Kasia", "Jan", "Anna", "Tomek", "Agnieszka", "Piotr", "Zosia"
};



Fan::Fan() {
    mtype = 1;
    generateRandomSFan();
}

void Fan::generateRandomSFan() {
    static constexpr size_t nameCount = sizeof(names) / sizeof(names[0]);

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> nameDist(0, nameCount - 1);
    std::uniform_int_distribution<> gateDist(1, 3);
    std::uniform_int_distribution<> clubDist(0, 1); // Tylko 2 wartości: REAL_MADRYT, FC_BARCELONA
    std::uniform_int_distribution<> ticketDist(0, 9); // 10% szans na VIP

    this->fanID = rand() % 10000;
    std::string tempName = names[nameDist(gen)];
    strncpy(this->name, tempName.c_str(), sizeof(this->name));  // **Bezpieczna kopia**
    this->name[sizeof(this->name) - 1] = '\0';  // **Zapewnienie zakończenia `\0`**

    this->gate = gateDist(gen);
    this->club = static_cast<Club>(clubDist(gen));

    if (ticketDist(gen) == 0) {
        this->ticketType = VIP;
    } else {
        this->ticketType = REGULAR;
    }

    this->status = OCZEKUJACY;
}

bool Fan::kontrolaBezpieczenstwa() const {
    return rand() % 100 >= 10; // 10% kibiców nie przechodzi kontroli
}

std::string Fan::getName() const {
    return name;
}

int Fan::getGate() const {
    return gate;
}

Club Fan::getClub() const {
    return club;
}

FanStatus Fan::getStatus() const {
    return status;
}

TicketType Fan::getTicketType() const {
    return ticketType;
}

void Fan::setStatus(FanStatus newStatus) {
    status = newStatus;
}
