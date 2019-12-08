#ifndef FG_WALL_HPP
#define FG_WALL_HPP

#include "Space.hpp"

class Wall : public Space {
protected:
public:
    Wall();
    int getCh();
};
#endif

