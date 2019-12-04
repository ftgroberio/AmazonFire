#ifndef FG_GAMELOGIC_HPP
#define FG_GAMELOGIC_HPP

#include <iostream>
#include "Field.hpp"
#include "Space.hpp"

class GameLogic {
protected:
public:
    GameLogic();
    ~GameLogic();
    void buildField(int, int);
};
#endif

//    for (int i = 1; i <= row; i++) {
//        for (int j = 1; j <= col; j++) {
//            if (i == 1 && j == 1) {
//                head = new Field;
//                tail = head;
//            } else if (i > 1 && j == 1) {
//                Field *ptr = new Field(0, head, nullptr, nullptr, nullptr);
//                head->down = ptr;
//                head = ptr;
//                tail = head;
//            } else if (j > 1) {
//                Field *ptr = new Field(0, nullptr, nullptr, tail, nullptr);
//                tail->right = ptr;
//                tail = ptr;
//            }
//            if (i > 1) {
//                Field *top, *next;
//                top = head->up;
//            }
//        }
//    }
