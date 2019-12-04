#include "Field.hpp"

Field::Field() {
    std::cout << "Field created" << std::endl;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
