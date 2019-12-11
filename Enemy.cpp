/*******************************************************************************
 * Program name: Final Project - SaveThePie - Enemy derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Enemy.hpp"

Enemy::Enemy() {
    this->data = 34;
    // this->data = ACS_DIAMOND;
    this->attr = COLOR_PAIR(7);
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Enemy::getCh() {
    // virtual?
    return this->data;
}

