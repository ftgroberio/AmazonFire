/*******************************************************************************
 * Program name: Final Project - SaveThePie - Fire derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Fire is a derived class from the base class Space.
 *              After the activation of a bomb node, the empty spaces and
 *              enemy spaces will be replaced by an explosion animation for
 *              around 500 milliseconds. After the animation is completed, the
 *              same spaces will be replaced by an empty space of the Field
 *              type.
 ******************************************************************************/
#ifndef FG_FIRE_HPP
#define FG_FIRE_HPP

#include "Space.hpp"

class Fire : public Space {
public:
    Fire();
    int getCh();
};
#endif
