//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Viewport Header

#ifndef PACMAN_VIEWPORT_H
#define PACMAN_VIEWPORT_H

#include <string>
#include <vector>
#include "Level.h"
#include "Position.h"
#include "Entity.h"
#include "Game.h"
using namespace std;

/*
 * Simple struct to register a type of object (level data or an entity)
 * to a unicode character
 */
struct Sprite {
    const char* unicodeForm; //Unicode form of this value
    int colorPairID; //ID of the color pair this object uses
};

/*
 * Viewport Driver implementation
 */
class Viewport {
private:
    static const int numSprites = 15;
    Sprite dataTypes[numSprites]; //Data type structures for given ID (id = index)

    int viewportWidth, viewportHeight; //Dimensions of the viewport
public:
    Viewport(); //Constructs a viewport, does nothing until initialized
    int getWidth();
    int getHeight();
    void initCurses(); //Initializes the ncurses library
    void exitCurses(); //Deinitializes ncurses
    void initDataTypes(); //Fills the ViewportDataValue types array
    Direction getKeyPressed(int key); //Returns the key currently being processed and turns it into a direction
    int getKeyPressedRaw(); //Returns the actual raw return of curses' getch()
    void render(Level level, string debugData); //Renders and prints the viewport
    bool isInsideViewport(Position playerPosition, Position pos); //Given a position determines if it is in the viewport
};

#endif //PACMAN_VIEWPORT_H
