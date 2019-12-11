/*******************************************************************************
 * Program name: Final Project - SaveThePie - Field derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Field.hpp"

Field::Field() {
    this->data = 32;
    this->attr = COLOR_PAIR(1);
    this->enter = true;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Field::getCh() { return this->data; }
