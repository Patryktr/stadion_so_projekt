#include "Stadion.h"
#include "Pracownik_tech.h"
#include "Kierownik.h"
#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int shmID;
int msgQueueID;
bool terminateSimulation = false;

void signal_handler(int sig) {
    if (sig == SIGINT) {
        std::cout << "[MAIN] Zatrzymywanie symulacji..." << std::endl;
        terminateSimulation = true;
        Pracownik_tech::stopWorkers(msgQueueID);
        msgctl(msgQueueID, IPC_RMID, NULL);
        shmctl(shmID, IPC_RMID, NULL);
        Stadion::releaseInstance();
        exit(0);
    }
}

int main() {
    signal(SIGINT, signal_handler);
    signal(SIGCHLD, SIG_IGN);

    shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    msgQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    auto stadion = Stadion::getInstance(100, shmID);
    std::vector<Gate*> gates = { stadion->getGate(1), stadion->getGate(2), stadion->getGate(3) };

    Pracownik_tech::startWorkers(gates, msgQueueID, shmID);

    if (fork() == 0) {
        Kierownik kierownik(stadion, shmID, msgQueueID);
        kierownik.nasluchujSygnaly();
        exit(0);
    }

    Pracownik_tech::tworzKibicow(100, shmID, msgQueueID);

    if (fork() == 0) {
        Pracownik_tech::obsluzKibica(stadion, shmID, msgQueueID);
        exit(0);
    }

    while (!terminateSimulation) {
        stadion->displayStatus();
        sleep(1);
    }

    Pracownik_tech::stopWorkers(msgQueueID);
    Stadion::releaseInstance();
    shmctl(shmID, IPC_RMID, NULL);

    return 0;
}
