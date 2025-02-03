#include "Gate.h"
#include <iostream>
#include <semaphore.h>
#include <unistd.h>

Gate::Gate(int capacity, string gate_name)
    : gateCapacity(capacity), gateName(gate_name), currentClub(static_cast<Club>(-1)), currentNumberOfFans(0) {

    if (sem_init(&gateSemaphore, 0, gateCapacity) == -1) {
        perror("sem_init failed");
        exit(1);
    }
}

Gate::~Gate() {
    sem_destroy(&gateSemaphore);
}

void Gate::leaveGate(Fan fan) {
    sleep(rand() % 10 + 10);  // Kibic zostaje w bramce przez 10-20 sekund

    if (currentNumberOfFans > 0) {  // **Nie pozwalamy zejść poniżej 0!**
        currentNumberOfFans--;
    } else {
        std::cerr << "[ERROR] Błąd! `currentNumberOfFans` w " << gateName << " spadło poniżej 0!\n";
        return;
    }

    std::cout << "[INFO] Kibic " << fan.getName() << " opuścił " << gateName
              << ". Pozostało w bramce: " << currentNumberOfFans << "\n";

    if (currentNumberOfFans == 0) {
        currentClub = static_cast<Club>(-1);
        std::cout << "[INFO] " << gateName << " jest teraz pusta i gotowa na nowych kibiców.\n";
    }

    sem_post(&gateSemaphore);  // **Zwalniamy semafor TYLKO jeśli kibic faktycznie wyszedł**
}




bool Gate::tryEnter(Fan fan) {
    if (sem_trywait(&gateSemaphore) == 0) {
        if (currentNumberOfFans == 0) {  // Bramka jest pusta, więc przypisujemy jej klub
            currentClub = fan.getClub();
            std::cout << "[DEBUG] Bramka " << gateName << " teraz przypisana do klubu: "
                      << (currentClub == REAL_MADRYT ? "Real Madryt" : "FC Barcelona") << ".\n";
        }

        if (fan.getClub() == currentClub) {
            std::cout << "[DEBUG] Kibic " << fan.getName() << " PRÓBUJE wejść do " << gateName << ".\n";

            usleep(50000); // Symulacja rejestracji kibica
            currentNumberOfFans++;

            std::cout << "[INFO] Kibic " << fan.getName() << " WESZEDŁ do " << gateName
                      << ". Aktualna liczba kibiców: " << currentNumberOfFans << "\n";

            return true;
        } else {
            std::cout << "[WARNING] Kibic " << fan.getName() << " NIE MOŻE wejść do " << gateName
                      << " (Bramka obsługuje inny klub!).\n";

            sem_post(&gateSemaphore);
            return false;
        }
    } else {
        std::cout << "[WARNING] Bramka " << gateName << " JEST PEŁNA. Kibic " << fan.getName() << " nie może wejść.\n";
        return false;
    }
}



bool Gate::hasSpaceAndAccepts(Club club) const {
    return currentNumberOfFans < gateCapacity && (currentClub == club || currentClub == static_cast<Club>(-1));
}

string Gate::getName() const {
    return gateName;
}
