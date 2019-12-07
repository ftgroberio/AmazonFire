#include "Tree.hpp"

Tree::Tree() {
    this->data = 32;
    this->attr = COLOR_PAIR(3) | A_BOLD;
    this->enter = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
