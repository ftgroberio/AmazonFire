#include "Wall.hpp"

Wall::Wall() {
    this->data = 32;
    this->attr = COLOR_PAIR(5);
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

int Wall::getCh() {
    // virtual?
    return this->data;
}
