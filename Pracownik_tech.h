#ifndef PRACOWNIK_TECH_H
#define PRACOWNIK_TECH_H

#include "Fan.h"
#include "Gate.h"
#include "Stadion.h"
#include <vector>
#include <sys/msg.h>
#include <csignal>
#include <unistd.h>

class Pracownik_tech {
public:
    static void tworzKibicow(int liczbaKibicow, int shmID, int msgQueueID);
    static void obsluzKibica(Stadion* stadion, int shmID, int msgQueueID);
    static void rozpocznijWychodzenieKibicow(int shmID, int liczbaKibicow);
    static void startWorkers(const std::vector<Gate*>& gates, int msgQueueID, int shmID);
    static void stopWorkers(int msgQueueID);
};

#endif // PRACOWNIK_TECH_H
