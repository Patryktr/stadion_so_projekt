#ifndef KIEROWNIK_H
#define KIEROWNIK_H

#include "Stadion.h"
#include "Pracownik_tech.h"
#include <csignal>
#include <iostream>
#include <unistd.h>

class Kierownik {
public:
    Kierownik(Stadion* stadion, int shmID, int msgQueueID);
    void nasluchujSygnaly();
    static void obsluzSigusr1(int sig);
    static void obsluzSigusr2(int sig);
    static void obsluzSigterm(int sig);
    static void odebranoInformacjeOOpuszczeniuStadionu();

private:
    static Stadion* stadion;
    static int shmID;
    static int msgQueueID;
    static bool pracownicyWstrzymani;
    static int liczbaKibicowOpuszczajacych;
};

#endif // KIEROWNIK_H
