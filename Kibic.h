//
// Created by patry on 11.01.2025.
//

#ifndef KIBIC_H
#define KIBIC_H
#include <string>
#include <unistd.h>
#include <stdio.h>


using namespace std;

enum Status {
    REGULAR,
    VIP
};

enum Club {
    FC_BARCELONA,
    REAL_MADRYT
};

class Kibic {
private:
    string name;
    string surname;
    unsigned int age;


    pid_t fanPid;
    Club club;
    Status status;



    void generateRandomData(unsigned int seed);

    void generateRandomStatus();

    void generateRandomClub();

public:


    Kibic();

    ~Kibic();

    bool isAdult();

    string getName();

    string getSurname();

    unsigned int getAge();

    Status getStatus();

    string getClubAsString();

    bool isVIP();

    bool isSameClub(Club otherClub);

    string getStatusAsString();
};


#endif //KIBIC_H
