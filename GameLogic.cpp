#include "GameLogic.hpp"

GameLogic::GameLogic() {
    initscr();
    // curs_set(0);  // hide cursor
    keypad(stdscr, TRUE);
    start_color();

    getmaxyx(stdscr, boardHeight, boardWidth);
    boardHeight = boardHeight - 5;
    board.createBoard(boardHeight - 1, boardWidth - 1);
    // std::cout << "Height: " << boardHeight << std::endl;
    // std::cout << "Width: " << boardWidth << std::endl;
    noecho();
    cbreak();  // don't interrupt for user input
    // timeout(1000);  // wait 500ms for key press
    this->buildField();
    while ((ch = getch()) != KEY_F(2)) {
        this->takeInput();
        this->movePlayer(cY, cX);
        refresh();
        this->bottomData();
        refresh();
    }
}
GameLogic::~GameLogic() {
    // remove windows
    endwin();
}
void GameLogic::buildField() {

    srand(time(NULL));
    for (cY = 1; cY < boardHeight; ++cY) {
        for (cX = 1; cX < boardWidth; ++cX) {

            attron(board.getSpace(cY, cX)->attr);
            mvaddch(cY, cX, board.getSpace(cY, cX)->data);
        }
    }
    board.swapSpace(new Box, 1, 1);
    attron(board.getSpace(1, 1)->attr);
    mvaddch(1, 1, board.getSpace(1, 1)->data);
    board.swapSpace(new Box, 2, 2);
    attron(board.getSpace(2, 2)->attr);
    mvaddch(2, 2, board.getSpace(2, 2)->data);

    cY = boardHeight / 2;
    cX = boardWidth / 2;
    move(cY, cX);
}
void GameLogic::takeInput() {
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
void GameLogic::movePlayer(int cYin, int cXin) {
    if (board.getSpace(cY, cX)->enter) {
        move(cY, cX);
        board.swapSpace(new Player, cY, cX);
        attron(board.getSpace(cY, cX)->attr);
        addch(board.getSpace(cY, cX)->data);
        move(pcY, pcX);
        board.swapSpace(new Field, pcY, pcX);
        attron(board.getSpace(pcY, pcX)->attr);
        addch(board.getSpace(pcY, pcX)->data);
        move(cY, cX);
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
    std::string ss = std::to_string(this->cY);
    printw("%s", ss.c_str());
    printw("  X: ");
    ss = std::to_string(this->cX);
    printw("%s", ss.c_str());
    printw("   ");
}
