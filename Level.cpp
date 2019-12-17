//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Level Class

#include "Level.h"
#include "Position.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <sstream>

using namespace std;

Level::Level() {

}

int Level::loadFromFile(string fileName) {
    //Open file stream
    ifstream fileStream;
    fileStream.open(fileName);

    //Ensure stream is open
    if(!fileStream.is_open()) {
        return -1;
    }

    //Read the first header line of the file
    string headerLine;
    vector<string> headerSplit;
    getline(fileStream, headerLine);
    boost::split(headerSplit, headerLine, boost::is_any_of(","));

    //Set variables from header
    this->width = stoi(headerSplit[0]);
    this->height = stoi(headerSplit[1]);
    this->id = stoi(headerSplit[2]);

    int dataCount = 0, lineNum = 0, coinsAdded = 0;
    string readLine;
    while(getline(fileStream, readLine)) {
        if(readLine.size() == 0) { break; }
        //Break string into characters then convert to shorts
        vector<char> v(readLine.begin(), readLine.end());
        for(int i = 0; i < width; i++) {
            char ch = v[i];
            cout << ch;
            short val;
            switch(ch) {
                case '-': {
                    val = 1;
                } break;
                case '+': {
                    val = 1;
                } break;
                case '|': {
                    val = 1;
                } break;
                case ' ': {
                    val = 2;
                } break;
                case 'G': {
                    val = 4;
                } break;
                case 'R': {
                    val = 5;
                } break;
                default: {
                    val = 0;
                } break;
            }
            setData(val, i, lineNum);
            if(val == 2) {
                coinsAdded++;
            } else if(val == 5) {
                this->ghostRespawn = Position(i, lineNum);
            }

            dataCount++;
        }
        cout << endl;
        lineNum++; //Move down the y-values
    }

    initialCoins = coinsAdded;
    numCoins = coinsAdded;

    return dataCount;
}

int Level::getWidth() {
    return width;
}

int Level::getHeight() {
    return height;
}

int Level::getLevelID() {
    return id;
}

short Level::getData(int x, int y) {
    if(x < 0 || y < 0 || x > width || y > height) {
        return -1; //Invalid position
    }

    return levelData[y][x];
}

bool Level::setData(short val, int x, int y) {
    if(x < 0 || y < 0 || x > width || y > height) {
        return false; //Invalid position
    }

    levelData[y][x] = val;
    return true;
}

vector<Ghost>& Level::getGhosts() {
    return ghosts;
}

vector<Direction> Level::getAvailablePaths(Position pos) {
    int x = pos.getX(), y = pos.getY();
    vector<Direction> paths;
    if(getData((x-1), y) != 1) {
        paths.push_back(Direction::LEFT);
    }

    if(getData((x+1), y) != 1) {
        paths.push_back(Direction::RIGHT);
    }

    if(getData(x, (y-1)) != 1) {
        paths.push_back(Direction::UP);
    }

    if(getData(x, (y+1)) != 1) {
        paths.push_back(Direction::DOWN);
    }

    return paths;
}

bool Level::isMoveableSpace(bool isPlayer, Position pos) {
    int px = pos.getX(), py = pos.getY();
    short data = getData(px, py);

    if(isPlayer && data != 1 && data != 4) {
        return true;
    }

    if(!isPlayer && data != 1) {
        return true;
    }

    return false;
}

int Level::getInitialCoins() {
    return initialCoins;
}

int Level::getRemainingCoins() {
    return numCoins;
}

void Level::setInitialCoins(int coins) {
    this->initialCoins = coins;
}

void Level::decreaseCoinCount(int num) {
    numCoins -= num;
}

bool Level::initGhosts() {
    //Find the positions of the ghost spawning area
    int ghostID = 0;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(getData(x, y) == 4) {
                //Found spawning position, add next ghost
                Position spawnPos = Position(x, y);
                GhostType ghostType;
                switch(ghostID) {
                    case 0: {
                        ghostType = GhostType::RED;
                    } break;
                    case 1: {
                        ghostType = GhostType::PINK;
                    } break;
                    case 2: {
                        ghostType = GhostType::BLUE;
                    } break;
                    case 3: {
                        ghostType = GhostType::GREEN;
                    } break;
                }

                Ghost ghost = Ghost(ghostType, spawnPos);
                ghosts.push_back(ghost);
                ghostID++;
            }
        }
    }

    return (ghosts.size() == 4);
}

int randomWithin(int min, int max) {
    return min + ( std::rand() % (max - min + 1 ));
}

bool Level::initPacman() {
    bool spawnFound = false;
    Position spawn;
    while(!spawnFound) {
        int x = randomWithin(1, width-1);
        int y = randomWithin(1, height-1);
        cout << x << "," << y << endl;
        cout << getData(x, y) << endl;
        if(getData(x, y) == 0 || getData(x, y) == 2) {
            //Found valid spawn position
            cout << "in if" << endl;
            spawn = Position(x, y);
            spawnFound = true;
            cout << "s1" << endl;
            setData(0, x, y);
            cout << "s2" << endl;
            break;
        }
    }
    cout << "out" << endl;
    vector<Direction> spawnDirection = getAvailablePaths(spawn);
    int t1 = Direction::LEFT;
    cout << t1 << endl;
    Direction d1 = spawnDirection.at(0);
    cout << (short)d1 << endl;
    this->player = Pacman(spawn, spawnDirection[0]);
    cout << "assigned" << endl;
    return true;
}

Direction getBestPath(Position origin, Position target, bool reverse, vector<Direction> openPaths) {
    Direction bestStep = Direction::NONE;
    float bestDistance = reverse ? -1000.0 : 10000.0;
    for(Direction direction : openPaths) {
        Position pos = origin.stepInDirection(direction, 1);
        float distance = pos.distance(target);
        if(distance < bestDistance && !reverse) {
            //Found new best distance (non-reverse mode)
            bestDistance = distance;
            bestStep = direction;
        } else if(distance > bestDistance && reverse) {
            //Found best flee path
            bestDistance = distance;
            bestStep = direction;
        }
    }

    return bestStep;
}

/*
 * Return codes:
 * 0 = no special actions
 * 1 = Pacman collected a coin
 * 2 = Pacman collected a powerup
 * 3 = Pacman collided with ghost and died
 * 4 = Pacman collided with ghost and ate it (powerup)
 */
int Level::processCollisions() {
    Position pacmanPosition = player.getPosition();

    //Check for collisions with ghosts first
    for(Ghost ghost : ghosts) {
        if(pacmanPosition.isEqual(ghost.getPosition())) {
            //Collision with a ghost, check powerup state
            if(player.hasPowerup()) {
                //Pacman has powerup, eat the ghost
                ghost.setBehavior(Behavior::EATEN);
                ghost.setDespawnTicks(15 * 10);
                player.incrementScore(100);
                return 4;
            } else {
                //Pacman died by the ghost
                return 3;
            }
        }
    }

    //Check for coin in position
    short data = getData(pacmanPosition.getX(), pacmanPosition.getY());
    if(data == 2) {
        //Collect the coin and remove it from the level
        player.incrementScore(10);
        decreaseCoinCount(1);
        setData(0, pacmanPosition.getX(), pacmanPosition.getY());
        return 1;
    } else if(data == 3) {
        //Collect the powerup and call for the game state to be changed
        player.incrementScore(50);
        player.setPowerState(true);
        player.setPowerTicks(0);
        setGhostsScattered();
        setData(0, pacmanPosition.getX(), pacmanPosition.getY());
        return 2;
    }

    //No actions required, allow game to step
    return 0;
}

void Level::setGhostsScattered() {
    for(Ghost ghost : ghosts) {
        ghost.setBehavior(Behavior::SCATTER);
    }
}

void Level::setGhostsDefaultBehavior() {
    for(Ghost ghost : ghosts) {
        ghost.setBehavior(ghost.getDefaultBehavior());
    }
}

Direction Level::getGhostStep(Ghost ghost) {
    //Get available paths
    vector<Direction> availablePaths = getAvailablePaths(ghost.getPosition());
    Behavior behavior = ghost.getBehavior();

    //If a ghost is eaten, check if the ghost should be despawned
    if(behavior == Behavior::EATEN) {
        if(ghost.getDespawnTicks() == 0) {
            //End the despawn period
            behavior = ghost.getDefaultBehavior();
            ghost.setBehavior(ghost.getDefaultBehavior());
        } else {
            //Lower despawn by one tick
            ghost.setDespawnTicks(ghost.getDespawnTicks() - 1);
        }
    }

    //Don't step for idle or eaten behaviors
    if(behavior == Behavior::IDLE || behavior == Behavior::EATEN) {
        return Direction::NONE;
    }

    //Do step for chase and block behaviors
    if(behavior == Behavior::CHASE || behavior == Behavior::BLOCK) {
        Position chasePosition = (behavior == Behavior::CHASE) ? player.getPosition() : player.getPosition().stepInDirection(player.getDirection(), 5);
        return getBestPath(ghost.getPosition(), chasePosition, false, availablePaths);
    }

    //Do step for patrol and random behaviors
    if(behavior == Behavior::PATROL || behavior == Behavior::RANDOM) {
        //Check if next position in the current direction is open
        if(isMoveableSpace(false, ghost.getPosition().stepInDirection(ghost.getDirection(), 1))) {
            //Step in same direction
            return ghost.getDirection();
        } else {
            //Change direction
            if(behavior == Behavior::PATROL) {
                //Try RIGHT then UP, otherwise go random
                if(count(availablePaths.begin(), availablePaths.end(), Direction::RIGHT)) {
                    return Direction::RIGHT;
                } else if(count(availablePaths.begin(), availablePaths.end(), Direction::UP)) {
                    return Direction::UP;
                }
            }

            //Change direction randomly
            return availablePaths[randomWithin(0, availablePaths.size())];
        }
    }

    //Do step for scatter behavior
    if(behavior == Behavior::SCATTER) {
        Position fleePosition = player.getPosition().stepInDirection(player.getDirection(), 1);
        return getBestPath(ghost.getPosition(), fleePosition, true, availablePaths);
    }

    //Defaultly return no direction
    return Direction::UP;
}

bool Level::stepAllGhosts() {
    bool movedAll = true;
    for(Ghost& ghost : ghosts) {
        Direction step = getGhostStep(ghost);
        if(step == Direction::NONE && (ghost.getBehavior() != Behavior::EATEN || ghost.getBehavior() != Behavior::IDLE)) {
            movedAll = false;
            continue;
        }

        ghost.setDirection(step);
        Position npos = ghost.getPosition().stepInDirection(step, 1);
        ghost.setPosition(npos);
    }

    return movedAll;
}

Pacman& Level::getPlayer() {
    return player;
}

string Level::getLevelHeader() {
    stringstream ss;
    ss << "DIR ";
    ss << (int)player.getDirection();
    ss << "LVL ";
    ss << id;
    ss << "      SCORE ";
    ss << player.getScore();
    ss << "      COINS ";
    ss << numCoins;
    return ss.str();
}