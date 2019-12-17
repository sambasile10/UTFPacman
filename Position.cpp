//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Position Class

#include "Position.h"
#include <cmath>

using namespace std;

Position::Position() {
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}

void Position::setX(int x) {
    this->x = x;
}

void Position::setY(int y) {
    this->y = y;
}

bool Position::isEqual(Position pos2) {
    return (x == pos2.getX() && y == pos2.getY());
}

float Position::distance(Position pos2) {
    return (float)sqrt(((float)pow((pos2.getX() - x), 2)) + (float)pow((pos2.getY() - y), 2));
}

Position Position::stepInDirection(int direction, int stepSize) {
    switch(direction) {
        case 0: {
            return Position(x, y - stepSize);
        } break;
        case 1: {
            return Position(x, y + stepSize);
        } break;
        case 2: {
            return Position(x - stepSize, y);
        } break;
        case 3: {
            return Position(x + stepSize, y);
        } break;
        case 4: {
            return Position(x, y);
        } break;
    }
}