//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Game Driver

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "Entity.h"
#include "Ghost.h"
#include "Level.h"
#include "Pacman.h"
#include "Position.h"
#include "Viewport.h"
using namespace std;

/*
 * Simple enum to determine what the game logic
 * should do
 */
enum class GameState : unsigned int {
    /*
     * INIT = Game loading or on the menu screen
     * WIN = Pacman won, show win screen and score
     * LOSS = Ghost ate pacman, show game over screen
     * ACTIVE = Game running per usual logic
     * ACTIVE_POWERUP = Game running with all ghosts in scatter behavior
     * ERROR = oops
     */
    INIT = 0, WIN = 1, LOSS = 2, ACTIVE = 3, ACTIVE_POWERUP = 4, ERROR = 99
};

//Implementation for the driver of the game
class Game {

};

#endif //PACMAN_GAME_H
