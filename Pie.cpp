/*******************************************************************************
 * Program name: Final Project - SaveThePie - Pie derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "Pie.hpp"

Pie::Pie() {
    this->data = ACS_PI;
    this->attr = COLOR_PAIR(8) | A_BOLD | A_ALTCHARSET;
    this->enter = false;
    this->movable = false;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
int Pie::getCh() { return this->data; }
