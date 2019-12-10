#include "Player.hpp"

Player::Player() {
    // this->data = 176;
    // this->data = ACS_DIAMOND;
    this->data = ACS_TTEE;
    // this->attr = COLOR_PAIR(4) | A_ALTCHARSET;
    this->attr = COLOR_PAIR(6) | A_ALTCHARSET;
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Player::getCh() {
    if (this->data == ACS_TTEE) {
        this->data = 88;
    } else {
        this->data = ACS_TTEE;
    }
    return this->data;
}
