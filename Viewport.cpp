//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Viewport Driver

/*
 * Contains initializers, variables, and update functions for the
 * viewport
 */

#include <iostream>
#include <vector>
#include <string>
#include <ncursesw/curses.h>
#include <unistd.h>
#include <cmath>
#include <locale.h>
#include <sstream>
#include "Position.h"
#include "Entity.h"
#include "Level.h"
#include "Viewport.h"
using namespace std;

int FPS = 30; //Run at 30 frames per second
char *const LOCALE = "en_US.UTF-8"; //UTF-8 locale
const int OFFSET_Y = 2;

Viewport::Viewport() {

}

//Initializes the ncurses library
void Viewport::initCurses() {
    setlocale(LC_ALL, LOCALE);
    /*
     * Initializes curses library options
     */
    initscr(); //Initialize the screen object (terminal is the screen)
    start_color(); //Starts color printing
    cbreak(); //Disable EOL checks
    curs_set(false); //Disable cursor being displayed
    noecho(); //Disable key presses being displayed
    nodelay(stdscr, TRUE); //Display wait on the get character function
    keypad(stdscr, TRUE); //Allows extended keys to be used (e.x. function keys)

    //Set the viewport dimensions
    viewportWidth = COLS;
    viewportHeight = LINES;

    //Initialize foreground/background color pairs
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); //Pacman colors
    init_pair(2, COLOR_WHITE, COLOR_WHITE); //Map structure and coin colors
    init_pair(3, COLOR_BLACK, COLOR_BLACK); //Black on black, empty space
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK); //Pink ghost
    init_pair(5, COLOR_CYAN, COLOR_BLACK); //Light blue ghost
    init_pair(6, COLOR_RED, COLOR_BLACK); //Red ghost and power up colors
    init_pair(7, COLOR_GREEN, COLOR_BLACK); //Green ghost (instead of Pacman OG orange)
    init_pair(8, COLOR_BLUE, COLOR_BLACK); //Ghost scatter color
    init_pair(9, COLOR_WHITE, COLOR_BLACK); //White on black

}

void Viewport::exitCurses() {
    clear();
    endwin();
}

int Viewport::getWidth() {
    return viewportWidth;
}

int Viewport::getHeight() {
    return viewportHeight;
}

//Fills the array of ViewportDataValues
void Viewport::initDataTypes() {
    Sprite EMPTY_SPACE, WALL, PACMAN_UP, PACMAN_DOWN, PACMAN_LEFT, PACMAN_RIGHT,
        GHOST_RED, GHOST_PINK, GHOST_BLUE, GHOST_GREEN, GHOST_PANIC, GHOST_EATEN, COIN, FOOD;

    EMPTY_SPACE.unicodeForm = " ";
    EMPTY_SPACE.colorPairID = 10;
    Viewport::dataTypes[0] = EMPTY_SPACE;

    WALL.unicodeForm = "+";
    WALL.colorPairID = 2;
    dataTypes[1] = WALL;

    PACMAN_UP.unicodeForm = "\xe1\x97\xa2";
    PACMAN_UP.colorPairID = 1;
    dataTypes[2] = PACMAN_UP;

    PACMAN_DOWN.unicodeForm = "\xe1\x97\xa3";
    PACMAN_DOWN.colorPairID = 1;
    dataTypes[3] = PACMAN_DOWN;

    PACMAN_LEFT.unicodeForm = "\xe1\x97\xa4";
    PACMAN_LEFT.colorPairID = 1;
    dataTypes[4] = PACMAN_LEFT;

    PACMAN_RIGHT.unicodeForm = "\xe1\x97\xa7";
    PACMAN_RIGHT.colorPairID = 1;
    dataTypes[5] = PACMAN_RIGHT;

    GHOST_RED.unicodeForm = "\xe1\x97\x9d";
    GHOST_RED.colorPairID = 6;
    dataTypes[6] = GHOST_RED;

    GHOST_PINK.unicodeForm = "\xe1\x97\x9d";
    GHOST_PINK.colorPairID = 4;
    dataTypes[7] = GHOST_PINK;

    GHOST_BLUE.unicodeForm = "\xe1\x97\x9d";
    GHOST_BLUE.colorPairID = 5;
    dataTypes[8] = GHOST_BLUE;

    GHOST_GREEN.unicodeForm = "\xe1\x97\x9d";
    GHOST_GREEN.colorPairID = 7;
    dataTypes[9] = GHOST_GREEN;

    GHOST_PANIC.unicodeForm = "\xe1\x97\x9d";
    GHOST_PANIC.colorPairID = 8;
    dataTypes[10] = GHOST_PANIC;

    GHOST_EATEN.unicodeForm = "\xe1\x97\x9d";
    GHOST_EATEN.colorPairID = 9;
    dataTypes[11] = GHOST_EATEN;

    COIN.unicodeForm = "*";
    COIN.colorPairID = 9;
    dataTypes[12] = COIN;

    FOOD.unicodeForm = "\xf0\x9f\x8d\x92";
    FOOD.colorPairID = 6;
    dataTypes[13] = FOOD;
}



//Converts a short level data to a sprite index
int getSpriteIndex(short levelData) {
    switch(levelData) {
        case 0: { return 0; } break;
        case 1: { return 1; } break;
        case 2: { return 12; } break;
        case 3: { return 13; } break;
        case 4: { return 0; } break;
        default: { return 0; } break;
    }
}

int Viewport::getKeyPressedRaw() {
    return getch();
}

Direction Viewport::getKeyPressed(int key) {
    //const char* dbk = to_string(key).c_str();
    //mvprintw(0, 0, dbk);
    //refresh();
    switch(key) {
        case KEY_UP: {
            return Direction::UP;
        } break;
        case KEY_DOWN: {
            return Direction::DOWN;
        } break;
        case KEY_LEFT: {
            return Direction::LEFT;
        } break;
        case KEY_RIGHT: {
            return Direction::RIGHT;
        } break;
        default: {
            return Direction::NONE;
        } break;
    }
}

//Renders and prints the viewport
void Viewport::render(Level level, string debugData) {
    clear();

    //Print debug data
    attron(COLOR_PAIR(9));
    mvprintw(1, 1, debugData.c_str());

    //Print the header of the level first
    //mvprintw(0, 1, to_string(getch()).c_str());
    mvprintw(0, 5, level.getLevelHeader().c_str());

    //To avoid constantly assigning color pairs, save the state of the current
    int activeColor = 9;

    //Print level data first, ignoring entities
    for(int y = 0; y < level.getHeight(); y++) {
        for(int x = 0; x < level.getWidth(); x++) {
            //Get the sprite of the level object
            Sprite cSprite = dataTypes[getSpriteIndex(level.getData(x, y))];

            if(cSprite.colorPairID != activeColor) {
                //Change color pair
                attron(COLOR_PAIR(cSprite.colorPairID));
                activeColor = cSprite.colorPairID;
            }

            //Print unicode character of space at the location
            mvprintw(y+OFFSET_Y, x, cSprite.unicodeForm);
        }
    }

    //Print ghosts, overriding level data
    for(Ghost ghost : level.getGhosts()) {
        Sprite gSprite = dataTypes[ghost.getSprite()];
        attron(COLOR_PAIR(gSprite.colorPairID));
        mvprintw(ghost.getPosition().getY()+OFFSET_Y, ghost.getPosition().getX(), gSprite.unicodeForm);
    }

    //Print Pacman
    Sprite pSprite = dataTypes[level.getPlayer().getSprite()];
    attron(COLOR_PAIR(1));
    mvprintw(level.getPlayer().getPosition().getY()+OFFSET_Y, level.getPlayer().getPosition().getX(), pSprite.unicodeForm);

    refresh();
}

bool Viewport::isInsideViewport(Position playerPosition, Position pos) {
    int x1 = playerPosition.getX() - floor(viewportWidth / 2);
    int x2 = x1 + floor(viewportWidth / 2) * 2;

    return (pos.getX() >= x1 && pos.getX() <= x2);
}