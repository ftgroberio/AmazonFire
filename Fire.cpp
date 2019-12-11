/*******************************************************************************
 * Program name: Final Project - SaveThePie - Fire derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Fire.hpp"

Fire::Fire() {
    this->data = ACS_CKBOARD;
    this->attr = COLOR_PAIR(9) | A_BLINK;
    this->enter = true;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Fire::getCh() { return this->data; }
