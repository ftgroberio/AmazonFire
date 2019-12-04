/*******************************************************************************
 * Program name: Lab 9
 * Author: Felipe Groberio
 * Date: November 27th, 2019
 * Description: this class creates double linked lists which can be implemented
 *              as queue or stacks. It also has functions to remove or add
 *              elements at the head or tail positions
 ******************************************************************************/
#ifndef FG_SPACE_HPP
#define FG_SPACE_HPP

#include <iostream>

class Space {
protected:
public:
    Space *up;
    Space *down;
    Space *left;
    Space *right;
    Space();
    ~Space();
    virtual int getCh() = 0;
};

#endif
