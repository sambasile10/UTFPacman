//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Entity Header

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include "Position.h"
using namespace std;

/*
 * Small enum to translate a direction to a numeric form
 */
enum Direction : unsigned short {
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, NONE = 4
};

/*
 * Structure that stores state variabless for entities (including the player)
 * (that need to be animated (position moves on x ticks)
 */
class Entity {
protected:
    int id; //ID of this entity in the world
    int entityType; //Type of entity
    Position position; //Position of this entity in the level
    Direction direction; //Vector of movement for this entity
public:
    Entity(); //Default constructor
    Entity(int id, int entityType, Position pos); //Parameterized constructor
    int getID();
    int getType();
    Position getPosition();
    Direction getDirection();
    void setID(int& id); //Set the world unique ID
    void setType(int& typeID); //Set the typeID
    void setPosition(Position& pos); //Set the position
    void setDirection(Direction& direction); //Set the direction
    void update(); //Updates the entities position according to the Direction
    virtual int getSprite(); //Returns the index of the sprite for this entity
};

#endif
