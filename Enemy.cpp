#include "Enemy.hpp"

Enemy::Enemy() {
    this->data = 32;
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

