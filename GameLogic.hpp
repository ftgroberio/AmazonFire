#ifndef FG_GAMELOGIC_HPP
#define FG_GAMELOGIC_HPP

#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include "Board.hpp"
#include <stdlib.h> /* srand, rand */
#include <unistd.h>
#include <time.h>

class GameLogic {
protected:
    int boardHeight, boardWidth, maxHeight, maxWidth, ch;
    Board board;

public:
    int cY, cX, pcY, pcX;
    GameLogic();
    ~GameLogic();
    void buildField();
    void takeInput();
    void movePlayer();
    void moveSpace(int, int, int, int);
    void bottomData();
    void refreshBoard();
};
#endif
