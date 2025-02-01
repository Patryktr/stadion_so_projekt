#ifndef PRACOWNIK_TECH_H
#define PRACOWNIK_TECH_H
#include "Fan.h"
#include "Gate.h"
#include <queue>
#include <mutex>
#include <vector>

class Pracownik_tech {
private:
    Gate* gate;
    static std::queue<Fan> fansQueue;
    static std::mutex queueMutex;
    static vector<pid_t> pracownicy;
    int msgQueueID;

public:
    Pracownik_tech(Gate* gate);
    static void dodajKibica(Fan fan);
    void obslugujKolejke();
    static void startWorkers(std::vector<Gate*>& gates);


    Pracownik_tech(Gate* gate, int msgQueueID);
    static void startWorkers(std::vector<Gate*>& gates, int msgQueueID);

    // Wysyłanie sygnału do rozpoczęcia pracy
    static void startProcessing();

    // Zatrzymywanie wszystkich pracowników
    static void stopWorkers(int msgQueueID);
};
#endif