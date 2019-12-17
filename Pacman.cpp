//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Pacman Class

#include "Pacman.h"
using namespace std;

Pacman::Pacman() {}

Pacman::Pacman(Position spawnPos, Direction spawnDirection) {
    this->id = 0;
    this->entityType = 0;
    this->score = 0;
    this->powerup = false;
    this->powerTicks = -1;
    this->position = spawnPos;
    this->direction = spawnDirection;
}

int Pacman::getScore() {
    return score;
}

bool Pacman::hasPowerup() {
    return powerup;
}

int Pacman::getPowerTicks() {
    return powerTicks;
}

void Pacman::setScore(int score) {
    this->score = score;
}

void Pacman::incrementScore(int score) {
    this->score += score;
}

void Pacman::setPowerState(bool power) {
    this->powerup = power;
}

void Pacman::setPowerTicks(int ticks) {
    this->powerTicks = ticks;
}

int Pacman::getSprite() {
    switch(direction) {
        case UP: {
            return 2;
        } break;
        case DOWN: {
            return 3;
        } break;
        case LEFT: {
            return 4;
        } break;
        case RIGHT: {
            return 5;
        } break;
        case NONE: {
            return 5;
        } break;
        default: {
            return 5;
        } break;
    }
}

