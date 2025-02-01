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
    Stadion* stadion = Stadion::getInstance(10);

    signal(SIGINT, signal_handler);

    shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int* sharedCount = (int*)shmat(shmID, NULL, 0);
    *sharedCount = 0;

    msgQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0666);


    std::vector<Gate*> gates = { stadion->getGate(1), stadion->getGate(2), stadion->getGate(3) };

    Pracownik_tech::startWorkers(gates, msgQueueID);


    for (int i = 0; i < 999; i++) {
        if (fork() == 0) {
            Fan fan;
            fan.generateRandomSFan();
            std::cout << "[DEBUG] Dodano kibica " << fan.getName()
                      << " (Bramka: " << fan.getGate() << ") do kolejki." << std::endl;
            msgsnd(msgQueueID, &fan, sizeof(Fan), 0);
            exit(0);
        }
    }
    Pracownik_tech::startProcessing();

    while (!terminateSimulation) {
        sleep(3); // Co 3 sekundy sprawdzamy stan stadionu
        stadion->displayStatus();
    }

    Pracownik_tech::stopWorkers(msgQueueID);
    Stadion::releaseInstance();
    return 0;
}
