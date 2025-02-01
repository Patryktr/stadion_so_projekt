//
// Created by patryk on 1/21/25.
//

#ifndef FAN_H
#define FAN_H
#include <string>
using namespace std;
enum Status {
    REGULAR,
    VIP,
    STANDARD_PARENT,
    STANDARD_KID
};

enum Club {
    FC_BARCELONA,
    REAL_MADRYT
};

class Fan {
private:
    string name;
    unsigned int age;
    unsigned int gate;
    Club club;
    Status status;
    pid_t fanPid;
    int passCount;



public:
    void generateRandomSFan();
    Fan();
    unsigned int  getGate();
    unsigned int  getAge();
    Club getClub();
    string getName();
    int getPassCount() const ;
    void incrementPassCount();
    void resetPassCount();
};



#endif //FAN_H
