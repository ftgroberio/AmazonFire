/*******************************************************************************
 * Program name: Final Project - SaveThePie - Wall derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Wall is a derived class from the base class Space. As the name
 *              implies, walls will represent a space not accessible by the
 *              user. Wall nodes are used for the boundaries of the board and
 *              also for the structures created  within the board. Every time
 *              a new level is reached, new structures are  be randomly
 *              generated. Walls are represented by the white color.
 ******************************************************************************/
#ifndef FG_WALL_HPP
#define FG_WALL_HPP

#include "Space.hpp"

class Wall : public Space {
public:
    Wall();
    int getCh();
};
#endif

