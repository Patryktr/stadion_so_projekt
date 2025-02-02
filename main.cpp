#include <csignal>
#include <iostream>

#include <sys/shm.h>
#include <sys/msg.h>

#include "Stadion.h"
#include "Fan.h"
#include "Gate.h"
#include "Pracownik_tech.h"
int shmID;
int msgQueueID;
bool terminateSimulation = false;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        std::cout << "Zatrzymywanie symulacji..." << std::endl;
        terminateSimulation = true;
        // Create an instance or ensure a valid instance of Pracownik_tech to call stopWorkers
        Pracownik_tech worker(nullptr);
        worker.stopWorkers(msgQueueID);
        msgctl(msgQueueID, IPC_RMID, NULL);
        shmctl(shmID, IPC_RMID, NULL);
        Stadion::releaseInstance();
        exit(0);
    }
}
int main() {

    signal(SIGINT, signal_handler);

    shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmID == -1) {
        perror("Błąd przy tworzeniu pamięci współdzielonej");
        exit(1);
    }

    msgQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    auto stadion = Stadion::getInstance(10, shmID);
    std::vector<Gate*> gates = { stadion->getGate(1), stadion->getGate(2), stadion->getGate(3) };

    Pracownik_tech::startWorkers(gates, msgQueueID, shmID);

    for (int i = 0; i < 11; i++) {
        if (fork() == 0) {

            Fan fan;
            fan.generateRandomSFan();
            if (i >= stadion->getCapacity()) {
                std::cout << "[INFO] Stadion jest pełny! Kibic " << fan.getName() << " nie może wejść." << std::endl;
                continue;
            }

            int* sharedFanCount = (int*)shmat(shmID, NULL, 0); // Dodana deklaracja

            if (*sharedFanCount >= stadion->getCapacity()) {
                std::cout << "[INFO] Stadion jest pełny! Kibic " << fan.getName() << " nie może wejść." << std::endl;
                shmdt(sharedFanCount);
                exit(0);
            }

            std::cout << "[DEBUG] Dodano kibica " << fan.getName()
                      << " (Bramka: " << fan.getGate() << ") do kolejki." << std::endl;
            msgsnd(msgQueueID, &fan, sizeof(Fan), 0);

            shmdt(sharedFanCount); // Zwolnienie pamięci współdzielonej
            exit(0);
        }
    }


    Pracownik_tech::startProcessing();

    while (!terminateSimulation) {
        stadion->displayStatus();
        sleep(1);
    }

    Pracownik_tech::stopWorkers(msgQueueID);
    Stadion::releaseInstance();
    shmctl(shmID, IPC_RMID, NULL);

    }


