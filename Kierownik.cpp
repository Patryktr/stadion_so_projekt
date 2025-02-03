#include "Kierownik.h"

Stadion* Kierownik::stadion = nullptr;
int Kierownik::shmID = 0;
int Kierownik::msgQueueID = 0;
bool Kierownik::pracownicyWstrzymani = false;
int Kierownik::liczbaKibicowOpuszczajacych = 0;

Kierownik::Kierownik(Stadion* stadion, int shmID, int msgQueueID) {
    Kierownik::stadion = stadion;
    Kierownik::shmID = shmID;
    Kierownik::msgQueueID = msgQueueID;
}

void Kierownik::nasluchujSygnaly() {
    signal(SIGUSR1, obsluzSigusr1);
    signal(SIGUSR2, obsluzSigusr2);
    signal(SIGTERM, obsluzSigterm);

    std::cout << "[Kierownik] Oczekuję na sygnały...\n";
    while (true) {
        pause(); // Czeka na sygnały
    }
}

void Kierownik::obsluzSigusr1(int sig) {
    std::cout << "[Kierownik] Otrzymano SIGUSR1 - Wstrzymuję wpuszczanie kibiców.\n";
    pracownicyWstrzymani = true;
}

void Kierownik::obsluzSigusr2(int sig) {
    std::cout << "[Kierownik] Otrzymano SIGUSR2 - Wznawiam wpuszczanie kibiców.\n";
    pracownicyWstrzymani = false;
}

void Kierownik::obsluzSigterm(int sig) {
    std::cout << "[Kierownik] Otrzymano SIGTERM - Wszyscy kibice muszą opuścić stadion!\n";
    liczbaKibicowOpuszczajacych = *stadion->getFanCount();
    Pracownik_tech::rozpocznijWychodzenieKibicow(shmID, liczbaKibicowOpuszczajacych);
}

void Kierownik::odebranoInformacjeOOpuszczeniuStadionu() {
    liczbaKibicowOpuszczajacych--;
    if (liczbaKibicowOpuszczajacych <= 0) {
        std::cout << "[Kierownik] Otrzymałem potwierdzenie - wszyscy kibice opuścili stadion!\n";
    }
}
