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
    this->fireTime = (rand() % 500) + 500;
}
int Fire::getCh() { return this->data; }
