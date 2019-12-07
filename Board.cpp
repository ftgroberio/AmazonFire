#include "Board.hpp"

Board::Board() {
    head = nullptr;
    tail = nullptr;
}
Board::~Board() {
    Space *ptr = head;
    while (ptr->up) {
        ptr = ptr->up;
    }

    while (ptr) {
        Space *colPtr = ptr;
        ptr = ptr->down;
        while (colPtr) {
            Space *garbage = colPtr;
            colPtr = colPtr->right;
            delete garbage;
        }
    }
}
void Board::createRow(int col) {
    for (int i = 1; i <= col; i++) {
        if (i == 1) {
            tail = new Tree;
            tail->up = head;
            if (head) {
                head->down = tail;
            }
            head = tail;
        } else if (i == col) {
            Space *newPtr = new Tree;
            tail->right = newPtr;
            newPtr->left = tail;
            tail = newPtr;

        } else {
            Space *newPtr = new Field;
            tail->right = newPtr;
            newPtr->left = tail;
            tail = newPtr;
        }
    }
}
void Board::linkRow() {
    Space *top = head->up;
    Space *bot = head;
    top->down = head;
    while (top->right) {
        top = top->right;
        bot = bot->right;
        top->down = bot;
        bot->up = top;
    }
}
void Board::printBoard() {
    Space *ptr = head;
    while (ptr->up) {
        ptr = ptr->up;
    }

    while (ptr) {
        Space *colPtr = ptr;
        while (colPtr) {
            std::cout << (int)colPtr->data;
            colPtr = colPtr->right;
        }
        std::cout << std::endl;
        ptr = ptr->down;
    }
}
Space *Board::getSpace(int row, int col) {
    Space *ptr = head;
    while (ptr->up) {
        ptr = ptr->up;
    }
    for (int i = 1; i < row; i++) {
        ptr = ptr->down;
    }
    for (int i = 1; i < col; i++) {
        ptr = ptr->right;
    }
    return ptr;
}
void Board::swapSpace(Space *ptrIn, int row, int col) {
    Space *remPtr = this->getSpace(row, col);
    Space *newPtr = ptrIn;
    Space *tempPtr = 0;

    // Disconnect old node, and link new node to top node
    if (remPtr->up) {
        tempPtr = remPtr->up;
        tempPtr->down = newPtr;
        newPtr->up = tempPtr;
    }
    // Disconnect old node, and link new node to bottom node
    if (remPtr->down) {
        tempPtr = remPtr->down;
        tempPtr->up = newPtr;
        newPtr->down = tempPtr;
    }
    // Disconnect old node, and link new node to left node
    if (remPtr->left) {
        tempPtr = remPtr->left;
        tempPtr->right = newPtr;
        newPtr->left = tempPtr;
    }
    // Disconnect old node, and link new node to right node
    if (remPtr->right) {
        tempPtr = remPtr->right;
        tempPtr->left = newPtr;
        newPtr->right = tempPtr;
    }

    // delete old node
    delete remPtr;
}
void Board::createBoard(int row, int col) {
    this->createRow(col);
    for (int i = 1; i < row; i++) {
        this->createRow(col);
        this->linkRow();
    }
    //    for (int i = 2; i < col; i++) {
    //        this->swapSpace(new Tree, 2, i);
    //    }
    // this->swapSpace(new Box, 1, 1);
}

