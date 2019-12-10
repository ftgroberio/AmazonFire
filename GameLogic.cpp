#include "GameLogic.hpp"
#include <typeinfo>

GameLogic::GameLogic() {
    srand(time(NULL));

    // Start counting the clock
    begin = std::chrono::high_resolution_clock::now();

    /************************************************
     ************ Ncurses configuration ************/
    initscr();
    start_color();
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);
    curs_set(0);  // hide cursor
    noecho();
    cbreak();      // don't interrupt for user input
    timeout(100);  // wait 500ms for key press
    /***********************************************/

    getmaxyx(stdscr, maxHeight, maxWidth);
    boardHeight = maxHeight - 5;
    boardWidth = maxWidth;
    play = true;
    this->pies = 1;
    while (play) {
        board = new Board;
        board->createBoard(boardHeight, boardWidth, this->pies);
        pass = true;
        int a;
        if (pies >= 5) {
            a = 5;
        } else {
            a = pies;
        }
        int time = 550 - a * 50;
        timeout(100);  // wait 500ms for key press
        while ((ch = getch()) != KEY_F(2) && pass && play) {
            this->refreshBoard();
            this->checkPlayer();
            this->takeInput();

            eb = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(eb - ee)
                    .count() >= time) {
                this->moveEnemies();
            }
            if (std::chrono::duration_cast<std::chrono::milliseconds>(
                    eb - spawnTime).count() >= 50) {
                board->addEnemy();
                spawnTime = std::chrono::high_resolution_clock::now();
            }
            this->bottomData();
        }
        delete board;
        this->pies++;
        timeout(10000);
    }
}
GameLogic::~GameLogic() {
    // remove windows
    timeout(10000);  // wait 500ms for key press
    getch();
    endwin();
    std::cout << "THANK YOU FOR PLAYING" << std::endl;
}
void GameLogic::refreshBoard() {
    for (int Y = 1; Y < boardHeight; ++Y) {
        for (int X = 1; X < boardWidth; ++X) {
            attron(board->getSpace(Y, X)->attr);
            mvaddch(Y, X, board->getSpace(Y, X)->data);
            attroff(board->getSpace(Y, X)->attr);
        }
    }
    refresh();
}
void GameLogic::takeInput() {
    cY = board->getSpaceY(board->playerPtr);
    cX = board->getSpaceX(board->playerPtr);
    pcY = cY;
    pcX = cX;
    switch (ch) {
        case KEY_LEFT: {
            cX--;
            break;
        }
        case KEY_RIGHT: {
            cX++;
            break;
        }
        case KEY_UP: {
            cY--;
            break;
        }
        case KEY_DOWN: {
            cY++;
            break;
        }
    }
    if (dynamic_cast<Pie*>(board->getSpace(cY, cX))) {
        board->swapSpace(new Field, cY, cX);
        board->pieArray.pop_back();
    }
    this->moveSpace(pcY, pcX, cY, cX);
    if (board->pieArray.empty()) {
        this->pass = false;
    }
}
bool GameLogic::checkSpace(int row, int col) {
    if (board->getSpace(row, col)->movable) {
        this->checkSpace(row + row - board->getSpaceY(board->playerPtr),
                         col + col - board->getSpaceX(board->playerPtr));
    } else if (board->getSpace(row, col)->enter) {
        return true;
    } else {
        return false;
    }
}
void GameLogic::checkPlayer() {
    int pY = board->getSpaceY(board->playerPtr);
    int pX = board->getSpaceX(board->playerPtr);
    if (this->checkSpace(pY + 1, pX) || this->checkSpace(pY - 1, pX) ||
        this->checkSpace(pY, pX + 1) || this->checkSpace(pY, pX - 1)) {
        this->play = true;
    } else {
        this->play = false;
    }
}
void GameLogic::moveSpace(int prevY, int prevX, int nextY, int nextX) {
    int moveY = nextY - prevY;
    int moveX = nextX - prevX;
    if (moveY != 0 || moveX != 0) {
        if (board->getSpace(nextY, nextX)->movable) {
            this->moveSpace(nextY, nextX, nextY + moveY, nextX + moveX);
        }
        if (board->getSpace(nextY, nextX)->enter) {
            board->changeSpace(prevY, prevX, nextY, nextX);
        }
    }
}
void GameLogic::moveSpaceNR(int prevY, int prevX, int nextY, int nextX) {
    int moveY = nextY - prevY;
    int moveX = nextX - prevX;
    if (moveY != 0 || moveX != 0) {
        if (board->getSpace(nextY, nextX)->enter) {
            board->changeSpace(prevY, prevX, nextY, nextX);
        } else if (std::abs(moveY)) {
            srand(time(NULL));
            switch (rand() % 2) {
                case 1: {
                    if (board->getSpace(nextY, nextX + 1)->enter) {
                        board->changeSpace(prevY, prevX, nextY, nextX + 1);
                        break;
                    }
                }
                case 0: {
                    if (prevX > board->getSpaceX(board->playerPtr) &&
                        board->getSpace(nextY, nextX - 1)->enter) {
                        board->changeSpace(prevY, prevX, nextY, nextX - 1);
                        break;
                    }
                }
            }
        } else if (std::abs(moveX)) {
            srand(time(NULL));
            switch (rand() % 2) {
                case 1: {
                    if (prevY > board->getSpaceY(board->playerPtr) &&
                        board->getSpace(nextY - 1, nextX)->enter) {
                        board->changeSpace(prevY, prevX, nextY - 1, nextX);
                        break;
                    }
                }
                case 0: {
                    if (board->getSpace(nextY + 1, nextX)->enter) {
                        board->changeSpace(prevY, prevX, nextY + 1, nextX);
                        break;
                    }
                }
            }
        }
    }
}
void GameLogic::moveEnemies() {
    int pY = board->getSpaceY(board->playerPtr);
    int pX = board->getSpaceX(board->playerPtr);
    for (int i = 0; i < board->enemyArray.size() / 4; i++) {
        int e = rand() % board->enemyArray.size();

        int eY = board->getSpaceY(board->enemyArray[e]);
        int eX = board->getSpaceX(board->enemyArray[e]);

        if (std::abs(eY - pY) > std::abs(eX - pX)) {
            if (eY > pY) {
                // player is above enemy
                this->moveSpaceNR(eY, eX, eY - 1, eX);
            } else {
                // player is below enemy
                this->moveSpaceNR(eY, eX, eY + 1, eX);
            }
        } else if (std::abs(eY - pY) < std::abs(eX - pX)) {
            eY = board->getSpaceY(board->enemyArray[e]);
            eX = board->getSpaceX(board->enemyArray[e]);
            if (eX > pX) {
                this->moveSpaceNR(eY, eX, eY, eX - 1);
            } else {
                this->moveSpaceNR(eY, eX, eY, eX + 1);
            }
        }
    }
    ee = std::chrono::high_resolution_clock::now();
}
void GameLogic::bottomData() {
    move(boardHeight + 2, 5);
    attroff(A_ALTCHARSET);
    attron(COLOR_PAIR(4));
    printw("Y: ");
    // std::string ss = std::to_string(this->cY);
    std::string ss = std::to_string(board->getSpaceY(board->playerPtr));
    printw("%s", ss.c_str());
    printw("  X: ");
    // ss = std::to_string(this->cX);
    ss = std::to_string(board->getSpaceX(board->playerPtr));
    printw("%s", ss.c_str());
    printw("   ");
    end = std::chrono::high_resolution_clock::now();
    ss = std::to_string(
        std::chrono::duration_cast<std::chrono::seconds>(end - begin).count());
    printw("        ");
    printw("%s", ss.c_str());
    printw("        ");
    ss = std::to_string(board->pieArray.size());
    printw("        ");
    printw("%s", ss.c_str());
    printw("        ");
}
