/*******************************************************************************
 * Program name: Final Project - SaveThePie - Pie derived class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Pie is a derived class from the base class Space. The objective
 *              of the game is to collect pies and survie the green enemies.
 *              Each level comes with an increase on the number of pies to be
 *              collected by the user. Pies are stored on a container which
 *              manages the number of pies the user has to collect.
 ******************************************************************************/
#ifndef FG_PIE_HPP
#define FG_PIE_HPP

#include "Space.hpp"

class Pie : public Space {
public:
    Pie();
    int getCh();
};
#endif
