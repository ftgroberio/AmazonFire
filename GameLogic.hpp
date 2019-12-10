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
    int boardHeight, boardWidth, maxHeight, maxWidth, ch, turn;
    int cY, cX, pcY, pcX, pies;
    std::chrono::high_resolution_clock::time_point begin, eb, moveEnemyTime,
        spawnTime, fireTime, nowTime;
    Board *board;
    bool replay,  // true = keeps playing, false = exit game
        isAlive,  // true = alive, false = dead;
        pass;     // true = keep collecting pies, false == all pies collected

public:
    GameLogic();
    ~GameLogic();
    void welcomeScreen();
    void gameOverScreen();
    void takeInput();
    void deathRay(int, int);
    void moveEnemyTo(int, int, int, int);
    void moveSpace(int, int, int, int);
    void bottomData();
    void refreshBoard();
    void enemyLogic();
    void moveEnemies();
    void checkPlayer();
    bool checkSpace(int, int);
};
#endif
