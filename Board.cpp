#include "Board.hpp"

Board::Board() {
    srand(time(NULL));
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
void Board::createBoard(int row, int col, int pies) {
    this->brow = row;
    this->bcol = col;
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

    int randQuant = (rand() % 3) + 1;
    for (int i = 0; i < randQuant; i++) {
        this->addObstacle(10, 20);
    }
    randQuant = (rand() % 10) + 13;
    for (int i = 0; i < randQuant; i++) {
        this->addObstacle(3, 16);
    }

    randQuant = (rand() % 8) + 12;
    for (int i = 0; i < randQuant; i++) {
        this->addObstacle(8, 6);
    }

    randQuant = (rand() % 7) + 20;
    for (int i = 0; i < randQuant; i++) {
        this->addObstacle(3, 6);
    }

    this->cleanWall();

    for (int i = 0; i < 40; i++) {
        this->addObject(new Bomb);
    }

    for (int i = 0; i < 20; i++) {
        this->addEnemy();
    }
    /* Add pies */
    while (!this->pieArray.empty()) {
        this->pieArray.pop_back();
    }
    for (int i = 0; i < pies; i++) {
        this->addPie();
    }
}
int Board::getSpaceY(Space *ptrIn) {
    Space *ptr = ptrIn;
    int y = 0;
    while (ptr) {
        ptr = ptr->up;
        y++;
    }
    return y;
}
int Board::getSpaceX(Space *ptrIn) {
    Space *ptr = ptrIn;
    int x = 0;
    while (ptr) {
        ptr = ptr->left;
        x++;
    }
    return x;
}
void Board::addObject(Space *ptrIn) {
    bool badLocation = true;
    int x, y;
    while (badLocation) {
        y = (rand() % (this->brow - 3)) + 2;
        x = (rand() % (this->bcol - 3)) + 2;
        if (dynamic_cast<Field *>(this->getSpace(y, x))) {
            this->swapSpace(ptrIn, y, x);
            badLocation = false;
        }
    }
}
void Board::cleanWall() {
    for (int i = 2; i < 4; i++) {
        for (int j = 2; j < bcol - 1; j++) {
            this->swapSpace(new Field, i, j);
        }
    }
    for (int i = brow - 3; i < brow - 1; i++) {
        for (int j = 2; j < bcol - 1; j++) {
            this->swapSpace(new Field, i, j);
        }
    }
    for (int i = 4; i < brow - 3; i++) {
        for (int j = 2; j < 5; j++) {
            this->swapSpace(new Field, i, j);
        }
    }
    for (int i = 4; i < brow - 3; i++) {
        for (int j = bcol - 4; j < bcol - 1; j++) {
            this->swapSpace(new Field, i, j);
        }
    }
}
void Board::addPie() {

    bool badLocation = true;
    int x, y;
    while (badLocation) {
        y = (rand() % (this->brow - 3)) + 2;
        x = (rand() % (this->bcol - 3)) + 2;
        if (dynamic_cast<Field *>(this->getSpace(y, x))) {
            this->swapSpace(new Pie, y, x);
            this->pieArray.push_back(this->getSpace(y, x));
            badLocation = false;
        }
    }
}
void Board::addEnemy() {

    bool badLocation = true;
    int x, y;
    while (badLocation) {
        y = (rand() % (this->brow - 3)) + 2;
        x = (rand() % (this->bcol - 3)) + 2;
        if (dynamic_cast<Field *>(this->getSpace(y, x))) {
            this->swapSpace(new Enemy, y, x);
            this->enemyArray.push_back(this->getSpace(y, x));
            badLocation = false;
        }
    }
}
void Board::removeEnemy(Space *eIn) {

    for (int i = 0; i < this->enemyArray.size(); i++) {
        if (enemyArray[i] == eIn) {
            enemyArray.erase(enemyArray.begin() + i);
            this->swapSpace(new Field, this->getSpaceY(eIn),
                            this->getSpaceX(eIn));
            return;
        }
    }
}
void Board::popBomb() {
    int pY = this->getSpaceY(this->playerPtr);
    int pX = this->getSpaceX(this->playerPtr);

    if (dynamic_cast<Bomb *>(this->getSpace(pY, pX - 1))) {
        this->swapSpace(new Field, pY, pX - 1);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY - 1, pX - 1))) {
        this->swapSpace(new Field, pY - 1, pX - 1);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY - 1, pX))) {
        this->swapSpace(new Field, pY - 1, pX);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY - 1, pX + 1))) {
        this->swapSpace(new Field, pY - 1, pX + 1);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY, pX + 1))) {
        this->swapSpace(new Field, pY, pX + 1);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY + 1, pX + 1))) {
        this->swapSpace(new Field, pY + 1, pX + 1);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY + 1, pX))) {
        this->swapSpace(new Field, pY + 1, pX);

    } else if (dynamic_cast<Bomb *>(this->getSpace(pY + 1, pX - 1))) {
        this->swapSpace(new Field, pY + 1, pX - 1);
    }
}
void Board::addObstacle(int row, int col) {

    bool badLocation = true;
    int attempts = 0;
    int x, y;
    while (badLocation) {
        y = (rand() % this->brow);
        x = (rand() % this->bcol);
        attempts++;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (dynamic_cast<Field *>(this->getSpace(y + i, x + j))) {
                    badLocation = false;
                } else {
                    badLocation = true;
                    i = 999;
                    j = 999;
                }
            }
        }
        if (attempts > 2) {
            return;
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            this->swapSpace(new Wall, y + i, x + j);
        }
    }
}
