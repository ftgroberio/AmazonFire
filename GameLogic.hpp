/*******************************************************************************
 * Program name: Final Project - SaveThePie - GameLogic class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: gameLogic implements an arcade game with a survivor aspect to
 *              it. The player is tasked to collect all the pies before it is
 *              surrounded by enemies. With each successful level, the player
 *              has to collect an ever increasing number of pies which are
 *              randomly scattered around the board, while being chased by an
 *              increasingly number of enemies and randomly generated maps.
 ******************************************************************************/
#ifndef FG_GAMELOGIC_HPP
#define FG_GAMELOGIC_HPP

#include <iostream>
#include <chrono>
#include <ncurses.h>
#include <curses.h>
#include <stdlib.h> /* srand, rand */
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "Board.hpp"

class GameLogic {
protected:
    int boardHeight, boardWidth, maxHeight, maxWidth, ch, turn, rate;

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
