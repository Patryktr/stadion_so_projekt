#ifndef FAN_H
#define FAN_H

#include <string>
#include <cstdlib>

enum Club { REAL_MADRYT, FC_BARCELONA };
enum FanStatus { OCZEKUJACY, KIBICUJE, NIE_PRZESZEDŁ_KONTROLI, OPUŚCIŁ_STADION };
enum TicketType { VIP, REGULAR };

class Fan {
public:
    long mtype; // **MUSI BYĆ PIERWSZE**
    int fanID;
    char name[20];  // **Zmienione na tablicę, aby uniknąć problemów z wskaźnikami**
    Club club;
    FanStatus status;
    TicketType ticketType;
    int gate;

    Fan();
    void generateRandomSFan();
    bool kontrolaBezpieczenstwa() const;

    std::string getName() const;
    int getGate() const;
    Club getClub() const;
    FanStatus getStatus() const;
    TicketType getTicketType() const;
    void setStatus(FanStatus newStatus);
};

#endif // FAN_H
