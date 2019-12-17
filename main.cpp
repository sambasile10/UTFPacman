#include <iostream>
#include <ncursesw/curses.h>
#include <unistd.h>
using namespace std;

char *const LOCALE = "en_US.UTF-8"; //UTF-8 locale

int main() {
    initscr(); //Initialize the screen object (terminal is the screen)
    start_color(); //Starts color printing
    cbreak(); //Disable EOL checks
    curs_set(false); //Disable cursor being displayed
    noecho(); //Disable key presses being displayed
    nodelay(stdscr, TRUE); //Display wait on the get character function
    keypad(stdscr, TRUE); //Allows extended keys to be used (e.x. function keys)

    int ch = -1;
    int x = 2, y = 2;
    while(ch != 97) {
        clear();
        ch = getch();
        switch(ch) {
            case KEY_UP: {
                y--;
            } break;
            case KEY_DOWN: {
                y++;
            } break;
            case KEY_LEFT: {
                x--;
            } break;
            case KEY_RIGHT: {
                x++;
            } break;
        }
        mvprintw(y, x, "a");
        refresh();
        usleep(1000 * 100);
    }
}

void old() {
    setlocale(LC_ALL, LOCALE);

    /*
    * Initializes curses library options
    */
    /*initscr(); //Initialize the screen object (terminal is the screen)
    start_color(); //Starts color printing
    cbreak(); //Disable EOL checks
    curs_set(false); //Disable cursor being displayed
    noecho(); //Disable key presses being displayed
    nodelay(stdscr, TRUE); //Display wait on the get character function
    keypad(stdscr, TRUE); //Allows extended keys to be used (e.x. function keys)

    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    clear();
    //attron(COLOR_PAIR(2));
    //mvprintw(2, 2, "\xe1\x97\xa6");

    for(int i = 0; i < 14; i++) {
        Sprite spr =
    }

    refresh();

    //char *const BLOCK = "\\xe1\\x97\\xa6";
    //char bc = (char)0x2588;
    //char *const BLOCK = reinterpret_cast<char *const>(bc);
    //"\xe2\x99\x94"
    //wcout << bc << endl;
    //std::cout << "\xe1\x97\xa6" <<std::endl;
    /*usleep(10000 * 1000);
    attron(1);
    for(int x = 0; x < 10; x++) {
        clear();
        mvprintw(0, x, BLOCK);
        refresh();
        usleep(250 * 1000);
    }*/

    /*
     * for(int i = 0; i < 14; i++) {
        attron(COLOR_PAIR(dataTypes[i].colorPairID));
        mvprintw(i, 3, dataTypes[i].unicodeForm);
    }
     */
}