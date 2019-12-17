//CSCI 1300
//Sam Basile
//Recitation 402
//Project 3 - Position Header

#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H

/*
 * Small structure to define a position (x, y) as
 * one object rather than having x, y everywhere
 */
class Position {
private:
    int x, y; //X and Y positions
public:
    Position(); //Default constructor, position will be 0, 0
    Position(int x, int y); //Parameterized constructor
    int getX(); //Returns x position
    int getY(); //Returns y position
    void setX(int x); //Set x position to given
    void setY(int y); //Set y position to given
    bool isEqual(Position pos2); //Check if the two positions are equivalent
    float distance(Position pos2);
    Position stepInDirection(int direction, int stepSize);
};

#endif //PACMAN_POSITION_H
