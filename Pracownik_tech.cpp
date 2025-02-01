#include "Pracownik_tech.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Stadion.h"

// **Inicjalizacja statycznej kolejki i mutexa**
std::queue<Fan> Pracownik_tech::fansQueue;
std::mutex Pracownik_tech::queueMutex;

Pracownik_tech::Pracownik_tech(Gate* gate) : gate(gate) {}



// **Dodawanie kibiców do wspólnej kolejki**
void Pracownik_tech::dodajKibica(Fan fan) {
    std::lock_guard<std::mutex> lock(queueMutex);
    fansQueue.push(fan);
    std::cout << "[DEBUG] Dodano kibica " << fan.getName()
              << " do kolejki. Aktualny rozmiar kolejki: " << fansQueue.size() << "\n";
}

// **Obsługa kolejki – każdy pracownik obsługuje wspólną kolejkę**
/*void Pracownik_tech::obslugujKolejke() {
    std::cout << "Pracownik Techniczny (Bramka " << gate->getName()
              << ") rozpoczął pracę. PID: " << getpid() << "\n";

    while (true) {
        Fan fan;
        bool hasFan = false;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!fansQueue.empty()) {
                fan = fansQueue.front();
                fansQueue.pop();
                hasFan = true;
                std::cout << "[DEBUG] Pobieram kibica " << fan.getName()
                          << " z kolejki. Pozostało w kolejce: " << fansQueue.size() << "\n";
            }
        }

        if (hasFan) {
            // **Tutaj pracownik obsługuje kibica**
        } else {
            std::cout << "[DEBUG] Brak kibiców w kolejce. Pracownik (Bramka "
                      << gate->getName() << ") czeka...\n";
            usleep(50000); // **Dodajemy małe opóźnienie, aby uniknąć nadmiernego pobierania**
        }
    }
}*/





/*
void Pracownik_tech::startWorkers(std::vector<Gate*>& gates) {
    std::vector<pid_t> pracownicy;

    for (Gate* gate : gates) {
        pid_t pid = fork();

        if (pid == 0) { // **Kod procesu potomnego**
            std::cout << "[DEBUG] Pracownik Techniczny (Bramka " << gate->getName()
                      << ") czeka na start...\n";
            usleep(1000000); // **Krótka pauza, aby wszystkie procesy zdążyły się uruchomić**

            Pracownik_tech pracownik(gate);
            pracownik.obslugujKolejke();
            exit(0);
        } else if (pid > 0) {
            pracownicy.push_back(pid);
        } else {
            std::cerr << "Błąd podczas tworzenia procesu!" << std::endl;
            exit(1);
        }
    }

    // **Czekamy na zakończenie procesów**
    for (pid_t pid : pracownicy) {
        waitpid(pid, nullptr, 0);
    }
}*/
void Pracownik_tech::obslugujKolejke() {
    Fan fan;
    auto stadion= Stadion:: getInstance(100);
    std::cout << "[DEBUG] Pracownik przy bramce " << gate->getName() << " rozpoczął obsługę kolejki!" << std::endl;

    while (true) {
        ssize_t result = msgrcv(msgQueueID, &fan, sizeof(Fan), 0, 0);

        if (result == -1) {
            perror("[ERROR] msgrcv nie powiodło się");
            continue; // Uniknięcie zakończenia procesu
        }

        std::cout << "[DEBUG] Otrzymano kibica " << fan.getName()
                  << " dla bramki " << gate->getName() << std::endl;

        if (gate->tryEnter(fan)) {
            stadion->addFan();
            std::cout << "Kibic " << fan.getName() << " wszedł przez "
                      << gate->getName() << std::endl;
        }
    }
}
std::vector<pid_t> Pracownik_tech::pracownicy; // Przechowuje PID-y procesów

Pracownik_tech::Pracownik_tech(Gate* gate, int msgQueueID)
    : gate(gate), msgQueueID(msgQueueID) {}

void Pracownik_tech::startWorkers(std::vector<Gate*>& gates, int msgQueueID) {
    for (Gate* gate : gates) {
        pid_t pid = fork();

        if (pid == 0) { // Proces potomny – czeka na sygnał do startu
            std::cout << "[DEBUG] Pracownik Techniczny (Bramka " << gate->getName()
                      << ") gotowy, czeka na sygnał...\n";
            signal(SIGCONT, SIG_DFL); // Ustawienie domyślnej akcji na SIGCONT
            pause(); // Czeka na SIGCONT
            Pracownik_tech pracownik(gate, msgQueueID);
            pracownik.obslugujKolejke();
            exit(0);
        } else if (pid > 0) {
            pracownicy.push_back(pid);
        } else {
            std::cerr << "Błąd podczas tworzenia procesu!" << std::endl;
            exit(1);
        }
    }
}

// **Teraz uruchamiamy pracowników jednocześnie**
void Pracownik_tech::startProcessing() {
    std::cout << "[DEBUG] Wszyscy pracownicy gotowi! Wysyłanie sygnału startu..." << std::endl;
    for (pid_t pid : pracownicy) {
        if (kill(pid, SIGCONT) == 0) {
            std::cout << "[DEBUG] Wysłano SIGCONT do procesu " << pid << std::endl;
        } else {
            perror("[ERROR] Błąd podczas wysyłania SIGCONT");
        }
    }
}


// **Zatrzymanie wszystkich procesów**
void Pracownik_tech::stopWorkers(int msgQueueID) {
    for (pid_t pid : pracownicy) {
        kill(pid, SIGTERM); // Zatrzymanie każdego procesu
    }
    msgctl(msgQueueID, IPC_RMID, NULL);
}




