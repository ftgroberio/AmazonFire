#ifndef FG_PLAYER_HPP
#define FG_PLAYER_HPP

#include "Space.hpp"

class Player : public Space {
protected:
public:
    Player();
    int getCh();
};
#endif
