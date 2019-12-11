/*******************************************************************************
 * Program name: Final Project - SaveThePie - Player derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Player is a derived class from the base class Space.
 *              It represents a the main character of this game, it occupies a
 *              node just like any other space of this game but it can
 *              interact with the other spaces, items and enemies. The Player
 *              node can be controlled with the arrow keys for movement and
 *              the space bar for using the bomb item.
 ******************************************************************************/
#ifndef FG_PLAYER_HPP
#define FG_PLAYER_HPP

#include "Space.hpp"

class Player : public Space {
public:
    Player();
    int getCh();
};
#endif
