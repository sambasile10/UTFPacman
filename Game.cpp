//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Game Class

#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include "Game.h"
using namespace std;

/*
 * Main driver of the game, holds the Level and Viewport objects
 */

//Game constants
const int TPS = 1; //5 ticks per second
const int POWERUP_TICKS = (TPS * 15); //Number of ticks a powerup lasts
const int DESPAWN_TICKS = (TPS * 10); //Number of ticks a ghost should be despawned for after being eaten

//Handler objects
Viewport viewport;
Level level;

//Game data objects
GameState state; //Current GameState
string playerName; //Name of the player
int totalTicks; //Total ticks elapsed

string getDebugData(int keyPressed, int npx, int npy, int npresolve) {
    stringstream ss;
    ss << "KEY ";
    ss << keyPressed;
    ss << "  STATE ";
    ss << (int)state;
    ss << "  TICKS ";
    ss << totalTicks;
    ss << "  PACMAN (";
    ss << level.getPlayer().getPosition().getX();
    ss << ", ";
    ss << level.getPlayer().getPosition().getY();
    ss << ")   ";
    ss << "NPOS (";
    ss << npx << ", " << npy << ")[" << npresolve << "]";
    return ss.str();
}

/*
 * Processes one tick of the game, or one update
 */
void tick() {
    //Get the key being pressed and move Pacman before all other updates
    Position playerPosition = level.getPlayer().getPosition();
    int keyPressed = viewport.getKeyPressedRaw();
    Direction playerDirection = viewport.getKeyPressed(keyPressed);
    level.getPlayer().setDirection(playerDirection);

    //Handle Pacman's powerup state
    if(level.getPlayer().hasPowerup()) {
        if(level.getPlayer().getPowerTicks() > POWERUP_TICKS) {
            //End the powerup
            level.getPlayer().setPowerState(false);
            level.getPlayer().setPowerTicks(-1);
            level.setGhostsDefaultBehavior();
            state = GameState::ACTIVE;
        } else {
            //Advanced the power ticks elapsed
            level.getPlayer().setPowerTicks(level.getPlayer().getPowerTicks() + 1);
        }
    }

    //If no key pressed, don't move Pacman
    int npx = 0, npy = 0, npresolve = 0; //Debug variables
    if(playerDirection != Direction::NONE) {
        //Step forward 1 space in the direction
        Position newPosition = playerPosition.stepInDirection(playerDirection, 1);
        if(level.isMoveableSpace(true, newPosition)) {
            //Next position is valid, move to it
            level.getPlayer().setPosition(newPosition);
            level.getPlayer().setDirection(playerDirection);
            npx = newPosition.getX(), npy = newPosition.getY();
        } else {
            npresolve = -1;
        }
    } else {
        npresolve = -2;
    }

    //Call the Level function to check for collisions with level objects/ghosts
    int collisionsVal = level.processCollisions();
    if(collisionsVal == 2) {
        //Pacman collected a powerup, change game state
        state = GameState::ACTIVE_POWERUP;
    } else if(collisionsVal == 3) {
        //Pacman collided with a ghost and died
        state = GameState::LOSS;
    } else if(collisionsVal == 4) {
        //Pacman collided with a ghost and ate it
    }

    //Check for win condition (0 coins left)
    if(level.getRemainingCoins() == 0) {
        //No coins left, player won
        state = GameState::WIN;
    }

    //Step all ghosts forward
    level.stepAllGhosts();

    //Get some debug data
    string debugData = getDebugData(keyPressed, npx, npy, npresolve);

    //Render the viewport
    viewport.render(level, debugData);

    totalTicks++;
}

bool loadLevel(string fileName) {
    cout << "Loading level " << fileName << endl;
    level = Level();
    int dataLoaded = level.loadFromFile(fileName);
    cout << "Level header: " << level.getWidth() << "x" << level.getHeight() << " id=" << level.getLevelID() << endl;
    int dataExpected = level.getWidth() * level.getHeight();
    cout << "loadFromFile returned " << dataLoaded << ", expecting " << dataExpected << endl;
    if(dataLoaded != dataExpected) {
        cout << "Loaded data mismatch, returning" << endl;
        return false;
    } else {
        cout << "Data matches, file loaded successfully!" << endl;
    }

    cout << "adding ghosts to map" << endl;
    bool initGhostsVal = level.initGhosts();
    if(initGhostsVal) {
        cout << "ghosts added!" << endl;
    } else {
        cout << "initGhosts returned false, returning" << endl;
        return false;
    }

    cout << "searching for pacman spawn point..." << endl;
    bool initPacmanVal = level.initPacman();
    if(initPacmanVal) {
        cout << "spawning pacman at (" << level.getPlayer().getPosition().getX() << "," << level.getPlayer().getPosition().getY() << ")" << endl;
    } else {
        cout << "spawning failed, returning";
        return false;
    }

    cout << "Successfully loaded level!" << endl;
    return true;
}

bool initViewport() {
    viewport = Viewport();
    viewport.initCurses();
    viewport.initDataTypes();

    cout << "constructed viewport (" << viewport.getWidth() << "x" << viewport.getHeight() << ")";
    return true;
}

void endGame() {
    usleep(1000 * 1000 * 10);
    viewport.exitCurses();
}

int main() {
    state = GameState::INIT;
    cout << "CSCI 1300 Pacman // Sam Basile" << endl;
    cout << "Name please: ";
    string nameInput;
    cin >> nameInput;
    playerName = nameInput;
    cout << endl;
    cout << "Welcome, " << playerName << "!" << endl;
    cout << "Enter a level file to load: ";
    string levelFile;
    cin >> levelFile;
    cout << endl;
    cout << "Alright, loading level: " << levelFile << endl;

    bool initVal = loadLevel(levelFile);
    if(!initVal) {
        cout << "Failed to initialize :(" << endl;
        return -1;
    }

    cout << endl << "Found your level, game will start shortly..." << endl;
    usleep(1000 * 1000 * 1);

    //Initialize the viewport
    initViewport();
    state = GameState::ACTIVE;

    //Loop game logic until the state changes
    bool run = true;
    while(run) {
        tick();

        //Check for win/loss condition to jump to
        if(state == GameState::WIN || state == GameState::LOSS) {
            run = false;
            break;
        }

        usleep((1000 * 1000) * 2);
    }

    endGame();
}