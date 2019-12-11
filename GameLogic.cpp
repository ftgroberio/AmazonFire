/*******************************************************************************
 * Program name: Final Project - SaveThePie - GameLogic class
 * Author: Felipe Groberio
 * Date: December 10th, 2019
 ******************************************************************************/
#include "GameLogic.hpp"

/*******************************************************************************
 * the contructor of GameLogic controls the flow of the game. A game will
 * start as soon as the program starts, and the user has the option to play
 * until the game is over or it can press 'q' to exit current game or the
 * whole program. The user can also choose to restart the game on the initial
 * level
 ******************************************************************************/
GameLogic::GameLogic() {
    srand(time(NULL));

    /************************************************
     ************ Ncurses configuration ************/
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);  // hide cursor
    noecho();
    cbreak();  // don't interrupt for user input
    getmaxyx(stdscr, maxHeight, maxWidth);
    init_pair(2, COLOR_RED, COLOR_BLUE);
    init_pair(6, COLOR_MAGENTA, COLOR_YELLOW);  // Player
    init_pair(7, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(8, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(18, COLOR_GREEN, COLOR_BLACK);
    /***********************************************/

    /* replay flag controls when the whole program should finish */
    this->replay = true;

    while (replay) {
        /* Display welcome screen and instructions */
        this->welcomeScreen();

        /* plays until the user is alive or user choses to exit */
        while (isAlive) {
            /* creates a new board, either because it is a new game or
             * because the user pregressed to a higher level */
            board = new Board;
            board->createBoard(boardHeight, boardWidth, this->pies);

            /* pass is a boolean flag that controls if the
             * player has collected enough pies */
            pass = true;

            /* the integers rate and turn control the rate in which
             * enemies move and spawn */
            if (pies >= 5) {
                rate = 5;
            } else {
                rate = pies;
            }
            this->turn = 550 - rate * 50;

            timeout(50);  // wait 50ms for key press

            /* play same board while the player is alive or it
             * has not collected enough pies */
            while (pass && isAlive) {

                /* updates the board characters */
                this->refreshBoard();

                /* updates the plyer */
                this->checkPlayer();

                /* detects user movement, quit key, or if the user has
                 * attempted to resize window */
                this->takeInput();

                /* manages enemies, movements */
                this->enemyLogic();

                /* updates the data plotted on the bottom
                 * of the screen */
                this->bottomData();
            }

            /* deletes the current board before creating a new one */
            delete board;

            /* updates the  number of pies */
            this->pies++;
            timeout(10000);
        }

        /* display game over */
        this->gameOverScreen();
    }
}
/*******************************************************************************
 * deletes ncurses screen and frees up memory
 ******************************************************************************/
GameLogic::~GameLogic() {
    // remove ncurses screen
    endwin();
}
/*******************************************************************************
 * plots welcome screen and game instructions
 ******************************************************************************/
void GameLogic::welcomeScreen() {
    clear();
    // Start counting the clock
    begin = std::chrono::high_resolution_clock::now();
    // Check if the console screen is too small
    if (maxHeight < 40 || maxWidth < 80) {

        printw("Terminal window size is too small.\n");
        printw("Please make adjustments and restart the game.\n");
        this->isAlive = false;

    } else {

        // Display welcome screen
        move(maxHeight / 2 - 5, maxWidth / 2 - 17);
        attron(COLOR_PAIR(7));
        addch(34);
        attroff(COLOR_PAIR(7));
        attron(COLOR_PAIR(18));
        printw(" SURVIVE THE GREEN VIRUS ");
        attron(COLOR_PAIR(7));
        addch(34);
        attroff(COLOR_PAIR(7));
        move(maxHeight / 2 - 3, maxWidth / 2 - 15);
        printw("Collect all the pies! ");
        attron(COLOR_PAIR(8));
        addch(ACS_PI);
        attroff(COLOR_PAIR(8));
        move(maxHeight / 2 - 2, maxWidth / 2 - 17);
        printw("Move ");
        attron(COLOR_PAIR(6));
        addch(34);
        attroff(COLOR_PAIR(6));
        printw(" using the arrow keys");
        move(maxHeight / 2, maxWidth / 2 - 18);
        printw("Use the bombs ");
        attron(COLOR_PAIR(2));
        addch(33);
        attroff(COLOR_PAIR(2));
        printw(" to kill enemies.");
        move(maxHeight / 2 + 1, maxWidth / 2 - 34);
        printw(
            "Push bombs closer to enemies and activate it with the spacebar.");

        move(maxHeight / 2 + 4, maxWidth / 2 - 15);
        attron(A_BLINK);
        printw("Press any key to start!");
        attroff(A_BLINK);
        timeout(1000000);
        getch();
        this->boardHeight = maxHeight - 5;
        this->boardWidth = maxWidth;
        this->pies = 1;
        this->isAlive = true;
    }
}
/*******************************************************************************
 * plots game over screen and gives user the option to play again or to exit
 * the game
 ******************************************************************************/
void GameLogic::gameOverScreen() {
    init_pair(11, COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(11));
    move(boardHeight, boardWidth / 2 - 24);
    printw("                                            ");
    move(boardHeight + 1, boardWidth / 2 - 24);
    printw("                 GAME OVER                  ");
    move(boardHeight + 2, boardWidth / 2 - 24);
    printw("                                            ");
    move(boardHeight + 3, boardWidth / 2 - 24);
    printw("                                            ");
    move(boardHeight + 4, boardWidth / 2 - 24);
    printw("                                            ");
    refresh();
    nowTime = std::chrono::high_resolution_clock::now();
    timeout(0);
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               nowTime - spawnTime).count() < 1200) {
        nowTime = std::chrono::high_resolution_clock::now();
        getch();
    }
    timeout(10000000);
    move(boardHeight + 3, boardWidth / 2 - 24);
    printw(" press [q] to exit or any key to play again ");
    refresh();
    if (getch() == 'q') {
        this->replay = false;
    } else {
        this->replay = true;
    }
    attroff(COLOR_PAIR(11));
}
/*******************************************************************************
 * enemyLogic controls when enemies are added to the board and when enemy
 * movements are performed
 ******************************************************************************/
void GameLogic::enemyLogic() {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            nowTime - moveEnemyTime).count() >= turn) {
        this->moveEnemies();
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            nowTime - spawnTime).count() >= 50) {
        board->addEnemy();
        spawnTime = std::chrono::high_resolution_clock::now();
    }
}
/*******************************************************************************
 * refreshes ncurse screen by reading each node of the board and passing
 * the character information and node attriutes to ncurses
 ******************************************************************************/
void GameLogic::refreshBoard() {
    /* cycle through every node on the board */
    for (int Y = 1; Y < boardHeight; ++Y) {
        for (int X = 1; X < boardWidth; ++X) {

            /* checks if this node is a fire node, if its, check
             * if it is time to put the fire out */
            if (dynamic_cast<Fire *>(board->getSpace(Y, X))) {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(
                        nowTime - fireTime).count() >= 350) {
                    board->swapSpace(new Field, Y, X);
                }
            }

            /* access a node, its ASCII character data, its
             * ncurses attributes, and plot the node on the screen */
            attron(board->getSpace(Y, X)->attr);
            mvaddch(Y, X, board->getSpace(Y, X)->data);
            attroff(board->getSpace(Y, X)->attr);
        }
    }
    /* updates the current time of the game for the bottom panel */
    nowTime = std::chrono::high_resolution_clock::now();

    /* refreshes the ncurses standard screen */
    refresh();
}
/*******************************************************************************
 * takeInput collects input from keyboard user interaction. The arrow keys
 * controls the Player node movement, the q-key quits the game, and KEY_RESIZE
 * detects if the user attempted to resize the screen. Lastly, the spacebar
 * is used to activate any Bomb spaces around the Player node
 ******************************************************************************/
void GameLogic::takeInput() {
    ch = getch();

    /* access Player node current position */
    cY = board->getSpaceY(board->playerPtr);
    cX = board->getSpaceX(board->playerPtr);

    /* pcY and  pcX are used to store previous coordinates */
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
        case 'q': {
            this->replay = false;
            this->isAlive = false;
            break;
        }
        case ' ': {
            board->popBomb();
            // start counting the time since last time a bomb was activated
            fireTime = std::chrono::high_resolution_clock::now();
            break;
        }
        case KEY_RESIZE: {
            // exit the game if screen is resized
            this->isAlive = false;
            break;
        }
    }
    board->collectPie(cY, cX);

    this->moveSpace(pcY, pcX, cY, cX);
    if (board->pieArray.empty()) {
        this->pass = false;
    }
}
/*******************************************************************************
 * checks if the player can enter a given node, or performes a push by
 * recursively calling checkSpace on the bomb object.
 ******************************************************************************/
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
/*******************************************************************************
 * checks if the player node is surrounded by enemy nodes, if it is, end the
 * current game by changing the isAlive boolean flag
 ******************************************************************************/
void GameLogic::checkPlayer() {
    int pY = board->getSpaceY(board->playerPtr);
    int pX = board->getSpaceX(board->playerPtr);
    if (this->checkSpace(pY + 1, pX) || this->checkSpace(pY - 1, pX) ||
        this->checkSpace(pY, pX + 1) || this->checkSpace(pY, pX - 1)) {
        this->isAlive = true;
    } else {
        this->isAlive = false;
    }
}
/*******************************************************************************
 * moves the player, if it can enter a given node, or performes a push by
 * recursively calling checkSpace on the bomb object. The recursive property
 * allows the user to push multipe objects at once.
 ******************************************************************************/
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
/*******************************************************************************
 * a very rudmentary algorithm in which attempts to shorten the distance of
 * enemy nodes to the player node
 ******************************************************************************/
void GameLogic::moveEnemyTo(int prevY, int prevX, int nextY, int nextX) {
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
/*******************************************************************************
 * cycles through the enemy array and initiates the movement of enemies towards
 * the player position.
 ******************************************************************************/
void GameLogic::moveEnemies() {
    int pY = board->getSpaceY(board->playerPtr);
    int pX = board->getSpaceX(board->playerPtr);
    for (int i = 0; i < board->enemyArray.size(); i++) {
        int eY = board->getSpaceY(board->enemyArray[i]);
        int eX = board->getSpaceX(board->enemyArray[i]);

        if (std::abs(eY - pY) > std::abs(eX - pX)) {
            if (eY > pY) {
                // player is above enemy
                this->moveEnemyTo(eY, eX, eY - 1, eX);
            } else {
                // player is below enemy
                this->moveEnemyTo(eY, eX, eY + 1, eX);
            }
        } else if (std::abs(eY - pY) < std::abs(eX - pX)) {
            eY = board->getSpaceY(board->enemyArray[i]);
            eX = board->getSpaceX(board->enemyArray[i]);
            if (eX > pX) {
                // player is to the left of enemy
                this->moveEnemyTo(eY, eX, eY, eX - 1);
            } else {
                // player is to the right of enemy
                this->moveEnemyTo(eY, eX, eY, eX + 1);
            }
        }
    }
    moveEnemyTime = std::chrono::high_resolution_clock::now();
}
/*******************************************************************************
 * updates the text information beneath the board
 ******************************************************************************/
void GameLogic::bottomData() {
    move(boardHeight, 3);
    attroff(A_ALTCHARSET);
    attron(COLOR_PAIR(4));
    printw("Y: ");
    std::string ss = std::to_string(board->getSpaceY(board->playerPtr));
    printw("%s", ss.c_str());
    printw("  X: ");
    ss = std::to_string(board->getSpaceX(board->playerPtr));
    printw("%s", ss.c_str());
    printw("   ");
    nowTime = std::chrono::high_resolution_clock::now();
    ss = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
        nowTime - begin).count());
    move(boardHeight + 1, 3);
    printw("Time: ");
    printw("%s", ss.c_str());
    printw("        ");
    ss = std::to_string(this->pies);
    move(boardHeight + 2, 3);
    printw("Level: ");
    printw("%s", ss.c_str());
    printw("        ");
    ss = std::to_string(abs(board->pieArray.size() - this->pies));
    move(boardHeight + 3, 3);
    printw("Pies collected: ");
    printw("%s", ss.c_str());
    ss = std::to_string(abs(board->pieArray.size()));
    move(boardHeight + 4, 3);
    printw("Pies remaining: ");
    printw("%s", ss.c_str());

    move(boardHeight, boardWidth / 2 - 22);
    printw("Collect the pies before you get infected!");
    move(boardHeight + 1, boardWidth / 2 - 23);
    printw("Get close to a bomb ");
    attron(COLOR_PAIR(6));
    addch(34);
    attron(COLOR_PAIR(2));
    addch(33);
    attron(COLOR_PAIR(4));
    printw(" and press [spacebar]");
    move(boardHeight + 3, boardWidth / 2 - 14);
    printw("press [q] to exit the game");
}
