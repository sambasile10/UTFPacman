//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Ghost Class

#include <vector>
#include "Ghost.h"
#include "Pacman.h"

using namespace std;

Ghost::Ghost(GhostType ghostType, Position position) {
    this->ghostType = ghostType;
    this->behavior = Behavior::IDLE;
    this->position = position;
    this->spawnPosition = position;

    //Get default behavior type
    switch(ghostType) {
        case GhostType::RED: {
            this->defaultBehavior = Behavior::CHASE;
            this->id = 1;
            this->entityType = 1;
        } break;

        case GhostType::BLUE: {
            this->defaultBehavior = Behavior::PATROL;
            this->id = 2;
            this->entityType = 2;
        } break;

        case GhostType::PINK: {
            this->defaultBehavior = Behavior::BLOCK;
            this->id = 3;
            this->entityType = 3;
        } break;

        case GhostType::GREEN: {
            this->defaultBehavior = Behavior::RANDOM;
            this->id = 4;
            this->entityType = 4;
        } break;
    }

    this->behavior = this->defaultBehavior;
}

Behavior Ghost::getBehavior() {
    return behavior;
}

void Ghost::setBehavior(Behavior behavior) {
    this-> behavior = behavior;
}

Behavior Ghost::getDefaultBehavior() {
    return defaultBehavior;
}

Position Ghost::getSpawnPosition() {
    return spawnPosition;
}

int Ghost::getDespawnTicks() {
    return ticksDespawned;
}

void Ghost::setDespawnTicks(int ticks) {
    this->ticksDespawned = ticks;
}

int Ghost::getSprite() {
    if(behavior == Behavior::SCATTER) {
        //Use the scatter sprite
        return 10;
    } else if(behavior == Behavior::EATEN) {
        //Use the eaten sprite
        return 11;
    }

    switch(ghostType) {
        case GhostType::RED: {
            return 6;
        } break;

        case GhostType::BLUE: {
            return 8;
        } break;

        case GhostType::PINK: {
            return 7;
        } break;

        case GhostType::GREEN: {
            return 9;
        } break;
    }
}

