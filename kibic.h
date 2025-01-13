//
// Created by patry on 11.01.2025.
//

#ifndef KIBIC_H
#define KIBIC_H
#include <string>
#include <thread>
using namespace std;


class kibic {
private:
    string name;
    string surname;
    unsigned int age;
    pid_t fanPid;

    void generateRandomData(unsigned int seed);

    public:
    kibic();
    ~kibic();
    bool isAdult();
    string getName();
    string getSurname();
    unsigned int getAge();

};


#endif //KIBIC_H
