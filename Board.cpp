#include "Board.hpp"

Board::Board() {
    head = nullptr;
    tail = nullptr;
}
Board::~Board() {
    Space *ptr = head->right;
    // std::cout << "Ptr: " << ptr << std::endl;
    while (ptr) {
        Space *garbage = ptr;
        ptr = ptr->right;
        std::cout << "DELETED" << std::endl;
        delete garbage;
    }
    std::cout << "DELETED" << std::endl;
    delete head;
}
void Board::createRow(int col) {
    for (int i = 1; i <= col; i++) {
        if (i == 1) {
            tail = new Field;
            tail->up = head;
            if (head) {
                std::cout << "HEAD IS NOT NULL" << std::endl;
                head->down = tail;
            }
            head = tail;
            head->data = i;
        } else {
            Space *newPtr = new Field;
            tail->right = newPtr;
            newPtr->left = tail;
            tail = newPtr;
            tail->data = i;
        }
    }
}
void Board::linkRow() {
    Space *top = head->up;
    Space *bot = head;
    while (top->right) {
        top = top->right;
        bot = bot->right;
        top->down = bot;
        bot->up = top;
    }
}
void Board::printData(int col) {
    Space *ptr = head;
    for (int i = 1; i < col; i++) {
        ptr = ptr->right;
    }
    std::cout << ptr->data << std::endl;
    ptr = ptr->up->right->right->down;
    std::cout << ptr->data << std::endl;
}
