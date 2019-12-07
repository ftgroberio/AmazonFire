#include "Player.hpp"

Player::Player() {
    this->data = ACS_DIAMOND;
    this->attr = COLOR_PAIR(4) | A_ALTCHARSET;
    this->enter = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
