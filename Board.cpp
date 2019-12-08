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
            tail = new Field;
            tail->up = head;
            if (head) {
                head->down = tail;
            }
            head = tail;
        } else if (i == col) {
            Space *newPtr = new Field;
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
void Board::changeSpace(int fromY, int fromX, int toY, int toX) {
    Space *fromPtr = this->getSpace(fromY, fromX);
    Space *toPtr = this->getSpace(toY, toX);
    Space *tempPtr = 0;

    Space *newField = new Field;
    if (fromPtr->up) {
        tempPtr = fromPtr->up;
        tempPtr->down = newField;
        newField->up = tempPtr;
    }
    if (fromPtr->down) {
        tempPtr = fromPtr->down;
        tempPtr->up = newField;
        newField->down = tempPtr;
    }
    if (fromPtr->left) {
        tempPtr = fromPtr->left;
        tempPtr->right = newField;
        newField->left = tempPtr;
    }
    if (fromPtr->right) {
        tempPtr = fromPtr->right;
        tempPtr->left = newField;
        newField->right = tempPtr;
    }
    // Disconnect old node, and link new node to top node
    if (toPtr->up) {
        tempPtr = toPtr->up;
        tempPtr->down = fromPtr;
        fromPtr->up = tempPtr;
    }
    // Disconnect old node, and link new node to bottom node
    if (toPtr->down) {
        tempPtr = toPtr->down;
        tempPtr->up = fromPtr;
        fromPtr->down = tempPtr;
    }
    // Disconnect old node, and link new node to left node
    if (toPtr->left) {
        tempPtr = toPtr->left;
        tempPtr->right = fromPtr;
        fromPtr->left = tempPtr;
    }
    // Disconnect old node, and link new node to right node
    if (toPtr->right) {
        tempPtr = toPtr->right;
        tempPtr->left = fromPtr;
        fromPtr->right = tempPtr;
    }

    // delete old node
    delete toPtr;
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
    for (int i = 1; i < col; i++) {
        this->swapSpace(new Wall, 1, i);
        this->swapSpace(new Wall, row - 1, i);
    }
    for (int i = 1; i < row; i++) {
        this->swapSpace(new Wall, i, 1);
        this->swapSpace(new Wall, i, col - 1);
    }
    this->swapSpace(new Player, row / 2, col / 2);
    playerPtr = this->getSpace(row / 2, col / 2);
}
int Board::getPlayerX() {
    Space *ptr = playerPtr;
    int x = 0;
    while (ptr) {
        ptr = ptr->left;
        x++;
    }
    return x;
}
int Board::getPlayerY() {
    Space *ptr = playerPtr;
    int y = 0;
    while (ptr) {
        ptr = ptr->up;
        y++;
    }
    return y;
}

