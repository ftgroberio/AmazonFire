#ifndef FG_BOARD_HPP
#define FG_BOARD_HPP

#include "Space.hpp"
#include "Field.hpp"
#include "Tree.hpp"
#include "Box.hpp"
#include "Player.hpp"
#include "TestSpace.hpp"  // delete this!!!!

class Board {
protected:
    Space *head, *tail;

public:
    Board();
    ~Board();
    void createRow(int);
    void linkRow();
    void printBoard();
    Space *getSpace(int, int);
    void swapSpace(Space *, int, int);
    void createBoard(int, int);
};
#endif
