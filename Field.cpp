#include "Field.hpp"

Field::Field() {
    this->data = 32;
    this->attr = COLOR_PAIR(1);
    this->enter = true;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
