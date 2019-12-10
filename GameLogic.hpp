#ifndef FG_GAMELOGIC_HPP
#define FG_GAMELOGIC_HPP

#include <iostream>
#include <chrono>
#include <ncurses.h>
#include <curses.h>
#include "Board.hpp"
#include <stdlib.h> /* srand, rand */
#include <unistd.h>
#include <time.h>
#include <math.h>

class GameLogic {
protected:
    int boardHeight, boardWidth, maxHeight, maxWidth, ch;
    std::chrono::high_resolution_clock::time_point begin, eb, ee, spawnTime,
        end;
    Board *board;
    bool play, pass;

public:
    int cY, cX, pcY, pcX, pies;
    GameLogic();
    ~GameLogic();
    void takeInput();
    void moveSpaceNR(int, int, int, int);
    void moveSpace(int, int, int, int);
    void bottomData();
    void refreshBoard();
    void moveEnemies();
    void checkPlayer();
    bool checkSpace(int, int);
};
#endif
