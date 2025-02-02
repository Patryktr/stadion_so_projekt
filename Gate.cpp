//
// Created by patryk on 1/27/25.
//

#include "Gate.h"

#include <iostream>
#include <semaphore.h>

#include <unistd.h>


Gate::Gate(int capacity, string gate_name): gateCapacity(capacity), gateName(gate_name),
                                            currentClub(static_cast<Club>(-1)) {
    // Inicjalizacja semafora lokalnego
    if (sem_init(&gateSemaphore, 0, gateCapacity) == -1) {
        perror("sem_init failed");
        exit(1);
    }
}

Gate::~Gate() {
    sem_destroy(&gateSemaphore);
}


void Gate::leaveGate(Fan fan) {
    currentNumberOfFans--;

    std::cout << "Fan " << fan.getName() << " opuścił " << gateName
            << ". Pozostało w bramce: " << currentNumberOfFans << "\n";

    // Jeśli bramka jest pusta, resetujemy jej przypisanie do klubu
    if (currentNumberOfFans == 0) {
        currentClub = static_cast<Club>(-1);
        std::cout << gateName << " jest teraz pusta i gotowa na nowych kibiców.\n";
    }

    sem_post(&gateSemaphore); // **Zwolnij miejsce w semaforze!**
}


bool Gate::tryEnter(Fan fan) {
    if (sem_trywait(&gateSemaphore) == 0) {
        // Sprawdź, czy jest miejsce
        if (currentNumberOfFans == 0) {
            currentClub = fan.getClub(); // Jeśli bramka pusta, przypisz jej klub
            cout << "Gate " << gateName << " is now assigned to "
                    << (currentClub == REAL_MADRYT ? "Real Madrid" : "FC Barcelona") << ".\n";
        }

        if (fan.getClub() == currentClub) {
            // **Symulacja rejestracji kibica (10% czasu kontroli)**
            usleep(50000); // 10% z 0.5 sekundy (kontrola trwa 0.5 sekundy)

            currentNumberOfFans++;
            cout << "Fan " << fan.getName() << " ("
                    << (fan.getClub() == REAL_MADRYT ? "Real Madrid" : "FC Barcelona")
                    << ") entered " << gateName << ". Current count: " << currentNumberOfFans << "\n";

            // **Symulacja czasu kontroli bezpieczeństwa**
            sleep(1);

            // Kibic opuszcza bramkę po kontroli
            leaveGate(fan);
            return true;
        } else {
            cout << "Fan " << fan.getName() << " ("
                    << (fan.getClub() == REAL_MADRYT ? "Real Madrid" : "FC Barcelona")
                    << ") cannot enter " << gateName << ". Club mismatch.\n";
            sem_post(&gateSemaphore); // Kibic nie pasuje do klubu, zwalnia miejsce
            return false;
        }
    } else {
        cout << "Gate " << gateName << " is full. Fan " << fan.getName() << " cannot enter.\n";
        return false; // Bramka pełna
    }
}

bool Gate::hasSpaceAndAccepts(Club club) const {
    {
        return currentNumberOfFans < gateCapacity && (currentClub == club || currentClub == static_cast<Club>(-1));
    }
}

string Gate::getName() const {
    return gateName;
}
