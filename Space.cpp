/*******************************************************************************
 * Program name: Lab 9
 * Author: Felipe Groberio
 * Date: November 27th, 2019
 ******************************************************************************/
#include "Space.hpp"

Space::Space() {
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_RED, COLOR_BLACK);
}
Space::~Space() {}
