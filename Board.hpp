/*******************************************************************************
 * Program name: Final Project - SaveThePie - Board class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Board class implements a 2D linked list, with each node having
 *              pointers to the four adjacent nodes (up, down, left and right).
 *              New boards are generated for every new level, complete with
 *              randomly generated obstacles. The board class also has member
 *              functions to manage and swap nodes.
 ******************************************************************************/
#ifndef FG_BOARD_HPP
#define FG_BOARD_HPP

#include <vector>

#include "Space.hpp"
#include "Field.hpp"
#include "Bomb.hpp"
#include "Fire.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Pie.hpp"
#include "Enemy.hpp"

class Board {
protected:
    Space *head, *tail;
    Space *playerPtr;
    int brow, bcol;
    std::vector<Space *> enemyArray, pieArray;

public:
    Board();
    ~Board();
    void createRow(int);
    void linkRow();
    Space *getSpace(int, int);
    void swapSpace(Space *, int, int);
    void createBoard(int, int, int);
    void changeSpace(int, int, int, int);
    int getSpaceY(Space *);
    int getSpaceX(Space *);
    void addObject(Space *);
    void cleanWall();
    void addEnemy();
    void removeEnemy(Space *);
    void popBomb();
    void bombExplosion(Space *);
    void collectPie(int, int);
    void addPie();
    void addObstacle(int, int);

    friend class GameLogic;
};
#endif
