/*******************************************************************************
 * Program name: Final Project - SaveThePie - Bomb derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Bomb is a derived class from the base class Space.
 *              Bombs are items that can be activated and will remove all
 *              enemies within a certain radius. A explosion animation will
 *              follow the activation of a bomb. Bombs are the only objects
 *              that can be pushed by the player. After bombs are activated,
 *              their node is removed and replaced by a field node.
 ******************************************************************************/
#ifndef FG_BOMB_HPP
#define FG_BOMB_HPP

#include "Space.hpp"

class Bomb : public Space {
public:
    Bomb();
    int getCh();
};
#endif
