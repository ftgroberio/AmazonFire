#include "Bomb.hpp"

Bomb::Bomb() {
    // this->data = ACS_LANTERN;
    this->data = 33;
    this->attr = COLOR_PAIR(2) | A_BOLD;
    this->enter = false;
    this->movable = true;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Bomb::getCh() {
    // virtual?
    return this->data;
}
