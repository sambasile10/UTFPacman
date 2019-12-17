//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Level Header

#ifndef PACMAN_LEVEL_H
#define PACMAN_LEVEL_H

#include <vector>
#include <string>
#include "Entity.h"
#include "Position.h"
#include "Ghost.h"
#include "Pacman.h"
using namespace std;

/*
 * Level data short types
 *
 * 0 = empty space
 * 1 = wall
 * 2 = coin (all empty spaces are coins/powerups until eaten)
 * 3 = powerup
 * 4 = ghost area (pacman can't go in here)
 * 5 = ghost respawn point
 */

class Level {
private:
    static const int maxHeight = 30;
    static const int maxWidth = 30;
    int width; //Size of x-axis of this level
    int height; //Size of y-axis of this level
    int id; //ID of this level
    int initialCoins; //Number of original coins in level
    int numCoins; //Number of coins remaining in the level
    short levelData[30][30]; //Game object types stored as shorts in a 2D array
    vector<Ghost> ghosts; //Entities in the level
    Pacman player; //Pacman player object
    Position ghostRespawn; //Ghost respawn position
public:
    Level(); //Constructor is always left empty
    int loadFromFile(string fileName);
    int getWidth();
    int getHeight();
    int getLevelID();
    int getInitialCoins();
    int getRemainingCoins();
    void setInitialCoins(int coins);
    void decreaseCoinCount(int num);
    short getData(int x, int y);
    bool setData(short val, int x, int y);
    bool isMoveableSpace(bool isPlayer, Position pos);
    vector<Ghost>& getGhosts();
    bool initGhosts();
    bool initPacman();
    void setGhostsScattered();
    void setGhostsDefaultBehavior();
    Pacman& getPlayer();
    vector<Direction> getAvailablePaths(Position pos);
    int processCollisions(); //Checks for collisions between Pacman and ghosts/powerups/coins
    Direction getGhostStep(Ghost ghost); //Get direction for ghost AI
    bool stepAllGhosts(); //Advance position of all ghosts
    string getLevelHeader(); //Generates the level header for the viewport
};

#endif //PACMAN_LEVEL_H
