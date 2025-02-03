#include "Pracownik_tech.h"

#include <algorithm>

#include "Kierownik.h"
#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
#include <cstdlib>
#include <random>
#include <sys/wait.h>

std::vector<pid_t> pracownicy;

void Pracownik_tech::obsluzKibica(Stadion* stadion, int shmID, int msgQueueID) {
    Fan fan;

    while (true) {
        ssize_t result = msgrcv(msgQueueID, &fan, sizeof(Fan) - sizeof(long), 0, 0);
        if (result == -1) {
            sleep(1);
            continue;
        }

        fan.name[sizeof(fan.name) - 1] = '\0';

        std::cout << "[DEBUG] Otrzymano kibica: " << fan.name << " (Klub: "
                  << (fan.getClub() == REAL_MADRYT ? "Real Madryt" : "FC Barcelona") << ") do kontroli.\n";

        if (!fan.kontrolaBezpieczenstwa()) {
            std::cout << "[INFO] Kibic " << fan.name << " NIE przeszedł kontroli bezpieczeństwa.\n";
            stadion->updateFanStatus(fan.fanID, NIE_PRZESZEDŁ_KONTROLI);
            continue;
        }

        int* sharedFanCount = (int*)shmat(shmID, NULL, 0);
        if (*sharedFanCount >= stadion->getCapacity()) {
            std::cout << "[INFO] Stadion pełny! Kibic " << fan.name << " nie może wejść.\n";
            shmdt(sharedFanCount);
            continue;
        }

        bool wszedl = false;
        std::vector<int> kolejnośćBram = {1, 2, 3};  // Lista kolejności bramek

        // 🔄 **Losowa zmiana kolejności sprawdzania bramek** (zapobiega skupianiu się na Bramka 1)
        std::shuffle(kolejnośćBram.begin(), kolejnośćBram.end(), std::mt19937(std::random_device()()));

        for (int i : kolejnośćBram) {  // Kibic sprawdza każdą bramkę
            Gate* gate = stadion->getGate(i);

            if (gate->hasSpaceAndAccepts(fan.getClub())) {
                std::cout << "[DEBUG] Kibic " << fan.name << " PRÓBUJE wejść do bramki " << gate->getName() << ".\n";
                if (gate->tryEnter(fan)) {
                    stadion->addFan(fan);
                    wszedl = true;
                    sleep(rand() % 10 + 10);  // Kibic pozostaje w bramce przez 10-20 sekund
                    gate->leaveGate(fan);
                    break;  // **Jeśli udało się wejść, nie próbujemy dalej**
                }
            }
        }

        if (!wszedl) {
            std::cout << "[WARNING] Kibic " << fan.name << " NIE znalazł dostępnej bramki i OPUŚCIŁ stadion.\n";
        }

        shmdt(sharedFanCount);
    }
}








void Pracownik_tech::startWorkers(const std::vector<Gate*>& gates, int msgQueueID, int shmID) {
    for (Gate* gate : gates) {
        pid_t pid = fork();

        if (pid == 0) { // **Kod procesu potomnego**
            std::cout << "[Pracownik Techniczny] Bramka " << gate->getName()
                      << " gotowa do obsługi.\n";
            Pracownik_tech::obsluzKibica(Stadion::getInstance(0, shmID), shmID, msgQueueID);
            exit(0);
        } else if (pid > 0) {
            pracownicy.push_back(pid);
        } else {
            std::cerr << "[ERROR] Błąd podczas tworzenia procesu pracownika!" << std::endl;
            exit(1);
        }
    }

    std::cout << "[Pracownik Techniczny] Wszyscy pracownicy gotowi!\n";
}

void Pracownik_tech::stopWorkers(int msgQueueID) {
    std::cout << "[Pracownik Techniczny] Kończenie pracy wszystkich pracowników...\n";

    for (pid_t pid : pracownicy) {
        kill(pid, SIGTERM);
    }

    for (pid_t pid : pracownicy) {
        waitpid(pid, nullptr, 0);
    }

    pracownicy.clear();

    msgctl(msgQueueID, IPC_RMID, NULL);
    std::cout << "[Pracownik Techniczny] Pracownicy zakończyli pracę.\n";
}

void Pracownik_tech::tworzKibicow(int liczbaKibicow, int shmID, int msgQueueID) {
    for (int i = 0; i < liczbaKibicow; i++) {
        if (fork() == 0) {
            Fan fan;
            fan.generateRandomSFan();

            std::cout << "[DEBUG] Tworzenie kibica: " << fan.name << " (Klub: "
                      << (fan.getClub() == REAL_MADRYT ? "Real Madryt" : "FC Barcelona") << ")\n";

            // **Używamy sizeof(fan) - sizeof(long), aby uniknąć problemów z pamięcią**
            if (msgsnd(msgQueueID, &fan, sizeof(Fan) - sizeof(long), 0) == -1) {
                perror("msgsnd error");
                exit(1);
            }
            exit(0);
        }
    }
}

void Pracownik_tech::rozpocznijWychodzenieKibicow(int shmID, int liczbaKibicow) {
    for (int i = 0; i < liczbaKibicow; i++) {
        if (fork() == 0) {
            sleep(rand() % 10 + 5);
            int* sharedFanCount = (int*)shmat(shmID, NULL, 0);
            if (*sharedFanCount > 0) {
                std::cout << "[INFO] Kibic opuszcza stadion. Pozostało kibiców: " << (*sharedFanCount - 1) << "\n";
                (*sharedFanCount)--;
            }
            shmdt(sharedFanCount);
            Kierownik::odebranoInformacjeOOpuszczeniuStadionu();
            exit(0);
        }
    }
}
