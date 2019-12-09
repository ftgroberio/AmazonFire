#ifndef FG_ENEMY_HPP
#define FG_ENEMY_HPP

#include "Space.hpp"

class Enemy : public Space {
protected:
public:
    Enemy();
    int getCh();
};
#endif

