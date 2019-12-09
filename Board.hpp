#ifndef FG_BOARD_HPP
#define FG_BOARD_HPP

#include "Space.hpp"
#include "Field.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Fire.hpp"
#include "Enemy.hpp"
#include <typeinfo>
#include <vector>

class Board {
protected:
    Space *head, *tail;
    Space *playerPtr;
    int brow, bcol, x, y;
    std::vector<Space *> enemyArray;

public:
    Board();
    ~Board();
    void createRow(int);
    void linkRow();
    void printBoard();
    Space *getSpace(int, int);
    void swapSpace(Space *, int, int);
    void createBoard(int, int);
    void changeSpace(int, int, int, int);
    int getSpaceY(Space *);
    int getSpaceX(Space *);
    void addObject(Space *);
    void addEnemy();

    friend class GameLogic;
};
#endif
