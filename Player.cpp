/*******************************************************************************
 * Program name: Final Project - SaveThePie - Player derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Player.hpp"

Player::Player() {
    this->data = 34;
    this->attr = COLOR_PAIR(6);
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Player::getCh() { return this->data; }
