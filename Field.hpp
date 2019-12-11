/*******************************************************************************
 * Program name: Final Project - SaveThePie - Field derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Field is a derived class from the base class Space.
 *              It represents an empty space that can be occupied by other
 *              Space-derived objects like the player, enemies or items.
 ******************************************************************************/
#ifndef FG_FIELD_HPP
#define FG_FIELD_HPP

#include "Space.hpp"

class Field : public Space {
public:
    Field();
    int getCh();
};
#endif
