#ifndef FG_BOARD_HPP
#define FG_BOARD_HPP

#include "Space.hpp"
#include "Field.hpp"

class Board {
protected:
    Space *head, *tail;

public:
    Board();
    ~Board();
    void createRow(int);
    void linkRow();
    void printData(int);
};
#endif
