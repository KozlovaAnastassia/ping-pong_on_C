#include <math.h>
#include <ncurses.h>
#include <stdio.h>

int field(int sc1, int sc2, int racket1, int racket2, int ballX, int ballY, int x, int y);

int main() {
    int x, y, sc1, sc2, racket1, racket2, ballX, ballY, directionX, directionY;

    x = 81;
    y = 26;
    sc1 = 0;
    sc2 = 0;
    ballX = 41;
    ballY = 13;
    directionY = 0;
    directionX = 0;
    racket1 = 13;
    racket2 = 13;

    initscr();

    noecho();

    curs_set(0);

    while (sc1 <= 21 || sc2 <= 21) {
        clear();
        field(sc1, sc2, racket1, racket2, ballX, ballY, x, y);
        refresh();

        napms(100);

        nodelay(stdscr, TRUE);

        char key = getch();

        switch (key) {
            case 'z':
                if (racket1 == 24) {
                    break;
                } else {
                    racket1++;
                    break;
                }
            case 'a':
                if (racket1 == 2) {
                    break;
                } else {
                    racket1--;
                    break;
                }
            case 'm':
                if (racket2 == 24) {
                    break;
                } else {
                    racket2++;
                    break;
                }
            case 'k':
                if (racket2 == 2) {
                    break;
                } else {
                    racket2--;
                    break;
                }
            case ' ':
                break;
            default:
                break;
        }

        if (directionY == 0) {
            ballY--;
        } else if (directionY == 1) {
            ballY++;
        }

        if (ballY - 1 == 0) {
            directionY = 1;
        } else if (ballY + 1 == 26) {
            directionY = 0;
        }

        if (directionX == 0) {
            ballX--;
            if (ballX - 1 == 3 && (ballY == racket1 || ballY == racket1 - 1 || ballY == racket1 + 1)) {
                directionX = 1;
            }
        } else if (directionX == 1) {
            ballX++;
            if (ballX + 1 == 78 && (ballY == racket2 || ballY == racket2 - 1 || ballY == racket2 + 1)) {
                directionX = 0;
            }
        }

        if (ballX + 1 == 80 && (ballY != racket2 || ballY != racket2 - 1 || ballY != racket2 + 1)) {
            sc1++;
            ballX = 41;
            ballY = 15;
            racket1 = 13;
            racket2 = 13;
            directionX = 1;
        } else if (ballX - 1 == 2 && (ballY != racket1 || ballY != racket1 - 1 || ballY != racket1 + 1)) {
            sc2++;
            ballX = 41;
            racket1 = 13;
            racket2 = 13;
            ballY = 15;
            directionX = 0;
        }

        if (sc1 == 21) {
            printw("First wins");
            endwin();
            break;
        } else if (sc2 == 21) {
            printw("Second wins");
            endwin();
            break;
        }
    }
    refresh();
    getch();
    endwin();
    return 0;
}

int field(int sc1, int sc2, int racket1, int racket2, int ballX, int ballY, int x, int y) {
    clear();
    do {
        for (int i = 0; x >= i; i++) {
            if (((y == 26) || (y == 0)) && (i <= 40)) {
                mvprintw(y, i, "#");
            } else {
                if ((y == 25) && (i == 40)) {
                    mvprintw(y, i, "%d|%d", sc1, sc2);
                    i = i + 3;
                } else {
                    if (ballX == i && ballY == y) {
                        mvprintw(y, i, "@");
                        i++;
                    }

                    if (((i == 0) || (i == 81)) && (y != 0) && (y != 26)) {
                        mvprintw(y, i, "#");
                        i = i + 2;
                    }

                    if ((i == 41) && (y != 0) && (y != 26)) {
                        if (ballX == i && ballY == y) {
                            mvprintw(y, i, "@");
                            i++;
                        } else {
                            mvprintw(y, i, "|");
                            i = i + 1;
                        }
                    }
                    if ((i == 3) && ((y == racket1) || (y == racket1 + 1) || (y == racket1 - 1))) {
                        mvprintw(y, i, "]");
                        i = i + 1;
                    }
                    if ((i == 79) && ((y == racket2) || (y == racket2 + 1) || (y == racket2 - 1))) {
                        mvprintw(y, i, "]");
                        i = i + 1;
                    }
                }
            }
            mvprintw(y, i, " ");
        }
        y = y - 1;

    }

    while (y >= 0);

    return 0;
}