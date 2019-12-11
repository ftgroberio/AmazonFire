/*******************************************************************************
 * Program name: Final Project - SaveThePie - Enemy derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Enemy is a derived class from the base class Space.
 *              Enemies are constantly spawning randomly around the map. Their
 *              sole objective is to surround the main character and leave
 *              the player with no remaining movements. Enemies can be killed
 *              by the bomb.
 *              Just like any other Space, each enemy is stored in its own
 *              node, which is deleted when the enemy dies. Enemies are
 *              managed by the board object, and are stored on an enemyArray.
 ******************************************************************************/
#ifndef FG_ENEMY_HPP
#define FG_ENEMY_HPP

#include "Space.hpp"

class Enemy : public Space {
public:
    Enemy();
    int getCh();
};
#endif

