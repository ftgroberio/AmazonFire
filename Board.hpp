#ifndef FG_BOARD_HPP
#define FG_BOARD_HPP

#include "Space.hpp"
#include "Field.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Player.hpp"

class Board {
protected:
    Space *head, *tail;
    Space *playerPtr;

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
    int getPlayerY();
    int getPlayerX();
};
#endif
