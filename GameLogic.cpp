#include "GameLogic.hpp"
#include <typeinfo>

GameLogic::GameLogic() {
    srand(time(NULL));
    initscr();
    start_color();
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    // curs_set(0);  // hide cursor
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, maxHeight, maxWidth);
    boardHeight = maxHeight - 5;
    boardWidth = maxWidth;
    board.createBoard(boardHeight, boardWidth);
    // std::cout << "Height: " << boardHeight << std::endl;
    // std::cout << "Width: " << boardWidth << std::endl;
    noecho();
    cbreak();  // don't interrupt for user input
    // timeout(1000);  // wait 500ms for key press
    this->buildField();
    while ((ch = getch()) != KEY_F(2)) {
        this->takeInput();
        this->moveSpace(pcY, pcX, cY, cX);
        // this->movePlayer();
        this->refreshBoard();
        this->bottomData();
        refresh();
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

    cY = boardHeight / 2;
    cX = boardWidth / 2;
    board.swapSpace(new Box, cY + 5, cX + 5);
    board.swapSpace(new Box, cY + 6, cX + 5);
    board.swapSpace(new Box, cY + 7, cX + 5);
}
void GameLogic::refreshBoard() {
    for (int Y = 1; Y < boardHeight; ++Y) {
        for (int X = 1; X < boardWidth; ++X) {
            attron(board.getSpace(Y, X)->attr);
            mvaddch(Y, X, board.getSpace(Y, X)->data);
        }
    }
    refresh();
}
void GameLogic::takeInput() {
    cY = board.getPlayerY();
    cX = board.getPlayerX();
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
    if (board.getSpace(nextY, nextX)->enter) {
        if (board.getSpace(nextY, nextX)->movable) {
            if (board.getSpace(nextY + moveY, nextX + moveX)->enter) {
                this->moveSpace(nextY, nextX, nextY + moveY, nextX + moveX);
                board.changeSpace(prevY, prevX, nextY, nextX);
            }

        } else {
            board.changeSpace(prevY, prevX, nextY, nextX);
        }
    }
}
void GameLogic::movePlayer() {
    int moveY, moveX;
    moveY = cY - pcY;
    moveX = cX - pcX;
    if (board.getSpace(cY, cX)->enter) {
        board.swapSpace(new Player, cY, cX);
        board.swapSpace(new Field, pcY, pcX);
    } else {
        cY = pcY;
        cX = pcX;
    }
}
void GameLogic::bottomData() {
    move(boardHeight + 2, 5);
    attroff(A_ALTCHARSET);
    attron(COLOR_PAIR(4));
    printw("Y: ");
    // std::string ss = std::to_string(this->cY);
    std::string ss = std::to_string(board.getPlayerY());
    printw("%s", ss.c_str());
    printw("  X: ");
    // ss = std::to_string(this->cX);
    ss = std::to_string(board.getPlayerX());
    printw("%s", ss.c_str());
    printw("   ");
}
