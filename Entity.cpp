//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Entity

#include <string>
#include "Entity.h"
#include "Level.h"
using namespace std;

Entity::Entity() {}

Entity::Entity(int id, int entityType, Position pos) {
    this->id = id;
    this->entityType = entityType;
    this->position = pos;
}

int Entity::getID() {
    return id;
}

void Entity::setID(int& id) {
    Entity::id = id;
}

int Entity::getType() {
    return entityType;
}

void Entity::setType(int& entityType) {
    Entity::entityType = entityType;
}

Direction Entity::getDirection() {
    return direction;
}

void Entity::setDirection(Direction& direction) {
    Entity::direction = direction;
}

Position Entity::getPosition() {
    return position;
}

void Entity::setPosition(Position& pos) {
    this->position = pos;
}

//Moves entity by 1 space in the current direction
void Entity::update() {
    int x = position.getX(), y = position.getY();
    switch(direction) {
        case UP: {
            Position npos = Position(x, y - 1);
            setPosition(npos);
        } break;
        case DOWN: {
            Position npos = Position(x, y - 1);
            setPosition(npos);
        } break;
        case LEFT: {
            Position npos = Position(x, y - 1);
            setPosition(npos);
        } break;
        case RIGHT: {
            Position npos = Position(x, y - 1);
            setPosition(npos);
        } break;
        case NONE: {
            //Don't change position
        } break;
        default: {
            //Don't change position
        } break;
    }
}

//Must be overriden by child class
int Entity::getSprite() {}

