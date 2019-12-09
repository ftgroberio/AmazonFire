#include "Fire.hpp"

Fire::Fire() {
    this->data = ACS_CKBOARD;
    this->attr = COLOR_PAIR(6) | A_BOLD | A_BLINK;
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Fire::getCh() {
    // delete
    return this->data;
}
