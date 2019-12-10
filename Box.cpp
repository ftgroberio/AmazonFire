#include "Box.hpp"

Box::Box() {
    this->data = ACS_LANTERN;
    this->attr = COLOR_PAIR(2) | A_BOLD | A_ALTCHARSET;
    this->enter = false;
    this->movable = true;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Box::getCh() {
    // virtual?
    return this->data;
}
