#include "Fire.hpp"

Fire::Fire() {
    this->data = 42;
    this->attr = COLOR_PAIR(9);
    this->enter = true;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Fire::getCh() { return this->data; }
