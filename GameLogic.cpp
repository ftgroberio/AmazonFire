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
    board.createBoard(boardHeight, boardWidth);
    // std::cout << "Height: " << boardHeight << std::endl;
    // std::cout << "Width: " << boardWidth << std::endl;
    this->buildField();
    refresh();
    play = true;
    while ((ch = getch()) != KEY_F(2) && play) {
        this->takeInput();
        this->moveSpace(pcY, pcX, cY, cX);

        eb = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(eb - ee)
                .count() >= 100) {
            this->moveEnemies();
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                eb - spawnTime).count() >= 100) {
            board.addEnemy();
            spawnTime = std::chrono::high_resolution_clock::now();
        }
        this->bottomData();
        this->refreshBoard();
    }
}
GameLogic::~GameLogic() {
    // remove windows
    endwin();
}
void GameLogic::buildField() {
    for (cY = 1; cY < boardHeight; ++cY) {
        for (cX = 1; cX < boardWidth; ++cX) {
            attron(board.getSpace(cY, cX)->attr);
            mvaddch(cY, cX, board.getSpace(cY, cX)->data);
        }
    }
}
void GameLogic::refreshBoard() {
    for (int Y = 1; Y < boardHeight; ++Y) {
        for (int X = 1; X < boardWidth; ++X) {
            attron(board.getSpace(Y, X)->attr);
            mvaddch(Y, X, board.getSpace(Y, X)->data);
            attroff(board.getSpace(Y, X)->attr);
        }
    }
    refresh();
}
void GameLogic::takeInput() {
    cY = board.getSpaceY(board.playerPtr);
    cX = board.getSpaceX(board.playerPtr);
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
}
void GameLogic::moveSpace(int prevY, int prevX, int nextY, int nextX) {
    int moveY = nextY - prevY;
    int moveX = nextX - prevX;
    if (moveY != 0 || moveX != 0) {
        if (board.getSpace(nextY, nextX)->movable) {
            this->moveSpace(nextY, nextX, nextY + moveY, nextX + moveX);
        }
        if (board.getSpace(nextY, nextX)->enter) {
            board.changeSpace(prevY, prevX, nextY, nextX);
        }
    }
}
void GameLogic::moveSpaceNR(int prevY, int prevX, int nextY, int nextX) {
    int moveY = nextY - prevY;
    int moveX = nextX - prevX;
    if (moveY != 0 || moveX != 0) {
        if (board.getSpace(nextY, nextX)->enter) {
            board.changeSpace(prevY, prevX, nextY, nextX);
        } else if (std::abs(moveY)) {
            if (prevX > board.getSpaceX(board.playerPtr) &&
                board.getSpace(nextY, nextX - 1)->enter) {

                board.changeSpace(prevY, prevX, nextY, nextX - 1);

            } else if (board.getSpace(nextY, nextX + 1)->enter) {

                board.changeSpace(prevY, prevX, nextY, nextX + 1);
            }
        } else if (std::abs(moveX)) {
            if (prevY > board.getSpaceY(board.playerPtr) &&
                board.getSpace(nextY - 1, nextX)->enter) {

                board.changeSpace(prevY, prevX, nextY - 1, nextX);

            } else if (board.getSpace(nextY + 1, nextX)->enter) {

                board.changeSpace(prevY, prevX, nextY + 1, nextX);
            }
        }
    }
}
void GameLogic::moveEnemies() {
    int pY = board.getSpaceY(board.playerPtr);
    int pX = board.getSpaceX(board.playerPtr);
    for (int i = 0; i < board.enemyArray.size() / 4; i++) {
        int e = rand() % board.enemyArray.size();

        int eY = board.getSpaceY(board.enemyArray[e]);
        int eX = board.getSpaceX(board.enemyArray[e]);
        if (std::abs(eY - pY) > std::abs(eX - pX)) {
            if (eY > pY) {
                // player is above enemy
                this->moveSpaceNR(eY, eX, eY - 1, eX);
            } else {
                // player is below enemy
                this->moveSpaceNR(eY, eX, eY + 1, eX);
            }
        } else {
            //            eY = board.getSpaceY(board.enemyArray[e]);
            //           eX = board.getSpaceX(board.enemyArray[e]);
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
    std::string ss = std::to_string(board.getSpaceY(board.playerPtr));
    printw("%s", ss.c_str());
    printw("  X: ");
    // ss = std::to_string(this->cX);
    ss = std::to_string(board.getSpaceX(board.playerPtr));
    printw("%s", ss.c_str());
    printw("   ");
    end = std::chrono::high_resolution_clock::now();
    ss = std::to_string(
        std::chrono::duration_cast<std::chrono::seconds>(end - begin).count());
    printw("        ");
    printw("%s", ss.c_str());
    printw("        ");
}
