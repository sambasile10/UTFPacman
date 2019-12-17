//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Ghost Class

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include "Entity.h"
#include "Pacman.h"

using namespace std;


//Small enum for ghost behavior types
typedef enum Behavior : unsigned int {
    /*
     * IDLE state doesn't allow the ghost to move
     *
     * CHASE is the primary state of the red ghost, it takes the
     * shortest path to Pacman
     *
     * BLOCK is the primary state of the pink ghost, it tries to go
     * to the spaces ahead of Pacman's direction
     *
     * PATROL is the primary state of the blue ghost, it just wanders around
     * the corner it spawned in
     *
     * RANDOM is the primary state of the green ghost, it just randomly
     * wanders the entire map
     *
     * SCATTER is when Pacman eats the cherry and all of the ghosts flee away from Pacman
     *
     * EATEN is when Pacman eats the ghost and it gets despawned for a while
     */
            IDLE = 0, CHASE = 1, BLOCK = 2, PATROL = 3, RANDOM = 4, SCATTER = 5, EATEN = 6
};

//Small enum for the type of the ghost (red, blue, pink ...)
typedef enum GhostType : unsigned int {
    RED = 0, PINK = 1, BLUE = 2, GREEN = 3
};

/*
 * Extends the Entity class to get more specific properties of a ghost
*/
class Ghost : public Entity {
private:
    Behavior behavior; //Current behavior of the ghost
    Behavior defaultBehavior; //Primary behavior of the ghost
    GhostType ghostType; //Type of ghost
    Position spawnPosition; //Spawn position of the ghost
    int ticksDespawned; //Number of ticks a ghost will remain despawned for
public:
    Ghost(GhostType ghostType, Position position); //Constructed by passing a ghost type
    int getSprite() override; //Override the Entity get sprite
    Behavior getBehavior(); //Returns the ghost behavior
    Behavior getDefaultBehavior(); //Returns the default behavior
    Position getSpawnPosition();
    int getDespawnTicks();
    void setDespawnTicks(int ticks);
    void setBehavior(Behavior behavior);
};


#endif //PACMAN_GHOST_H
