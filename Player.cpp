#include "Player.hpp"

Player::Player() {
    // this->data = 88;
    this->data = ACS_DIAMOND;
    this->attr = COLOR_PAIR(4) | A_ALTCHARSET;
    this->enter = false;
    this->movable = true;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Player::getCh() {
    // virtual?
    return this->data;
}
