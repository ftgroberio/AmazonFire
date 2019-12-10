#ifndef FG_FIRE_HPP
#define FG_FIRE_HPP

#include "Space.hpp"

class Fire : public Space {
protected:
    int fireTime;

public:
    Fire();
    int getCh();
};
#endif
