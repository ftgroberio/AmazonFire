#ifndef FG_FIELD_HPP
#define FG_FIELD_HPP

#include "Space.hpp"

class Field : public Space {
protected:
public:
    Field();
    ~Field();
    int getCh();
    void startField();
};
#endif
