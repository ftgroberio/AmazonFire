/*******************************************************************************
 * Program name: Lab 9
 * Author: Felipe Groberio
 * Date: November 27th, 2019
 ******************************************************************************/
#include "Space.hpp"

Space::Space() {
    init_pair(1, COLOR_BLACK, COLOR_BLACK);     // Empty field
    init_pair(2, COLOR_RED, COLOR_BLUE);        // Bomb
    init_pair(4, COLOR_RED, COLOR_BLACK);       // Botton data
    init_pair(5, COLOR_WHITE, COLOR_WHITE);     // Walls
    init_pair(6, COLOR_MAGENTA, COLOR_YELLOW);  // Player
    init_pair(7, COLOR_MAGENTA, COLOR_GREEN);   // Enemies
    init_pair(8, COLOR_YELLOW, COLOR_MAGENTA);  // Pies
    init_pair(9, COLOR_RED, COLOR_YELLOW);      // Fire
}
Space::~Space() {}
