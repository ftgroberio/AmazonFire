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
    void printBoard();
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
