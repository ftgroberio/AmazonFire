/*******************************************************************************
 * Program name: Final Project - SaveThePie - Bomb derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Bomb.hpp"

Bomb::Bomb() {
    this->data = 33;
    this->attr = COLOR_PAIR(2) | A_BOLD;
    this->enter = false;
    this->movable = true;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Bomb::getCh() { return this->data; }
