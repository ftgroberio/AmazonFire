/*******************************************************************************
 * Program name: Final Project - SaveThePie
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 * Description: Space is the base class for the types of spaces available for
 *              the iteration of this game: Field (representing empty spaces),
 *              Player, Enemy, Pie (items to be collected), Bomb (weapon), and
 *              Fire (bomb animation), and Wall.
 *              Each Space represents a node on a 2D linked list, which
 *              represents a board where the arcade game is played. Each node
 *              has four pointers to it's adjacent nodes. The 2D linked list
 *              is implemented and controlled by the class Board.
 ******************************************************************************/
#ifndef FG_SPACE_HPP
#define FG_SPACE_HPP

#include <iostream>
#include <ncurses.h>

class Space {
public:
    /* INT data holds the ASCII value which represents that
     * space and it is plotted by ncurses.
     * INT attr hold the attribute information and it is also
     * interpreted by ncurses. The used attributes are color information
     * and type of display (bold, blinking) */
    int data, attr;

    /* The boolean flags enter and movable are related to movement of the
     * player. If the flag enter is true, the player may enter that space which
     * may or may not be occupied.
     * The boolean flag movable is true if the player is allowed to move that
     * box. Currently, the only space that allows the player to move is the
     * Bomb object. */
    bool enter, movable;

    /* Each space is a node on a 2D linked list that simulates a board. Each
     * node
     * has four pointers to the adjacent nodes. */
    Space *up;
    Space *down;
    Space *left;
    Space *right;

    /* The space contructor holds color definitions for each of the derived
     * classes. */
    Space();
    ~Space();

    /* getCh() is a virtual function that returns the ASCII character that
     * represents each specific derived space. */
    virtual int getCh() = 0;
};
#endif
