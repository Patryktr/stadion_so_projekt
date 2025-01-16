//
// Created by patry on 13.01.2025.
//

#ifndef STADION_H
#define STADION_H



class Stadion {
private:
    int capacity;
    int currentNumberOfFans;
    static Stadion* instance;

    Stadion (int maxCapacity):capacity(maxCapacity),currentNumberOfFans(0){}
public:
    //uzywam singletona
    static Stadion* getInstance(int maxCapacity);
    bool admitFan();
    bool removeFan();
    void clearStadium();
    int getCurrentNumberOfFans();
    int getCapacity();

};



#endif //STADION_H
