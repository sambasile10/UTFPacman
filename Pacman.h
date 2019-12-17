//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Pacman Header

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "Entity.h"
using namespace std;

class Pacman : public Entity {
private:
    int score; //Current level score
    bool powerup; //True if Pacman has the power up to eat ghosts
    int powerTicks; //Number of ticks Pacman has had the powerup for (-1 if no powerup)
public:
    Pacman(Position spawnPos, Direction spawnDirection);

    Pacman();

    int getScore();
    void setScore(int score);
    void incrementScore(int score);
    bool hasPowerup();
    void setPowerState(bool power);
    int getPowerTicks();
    void setPowerTicks(int ticks);
    int getSprite() override; //Override the Entity getSprite function
};

#endif //PACMAN_PACMAN_H
