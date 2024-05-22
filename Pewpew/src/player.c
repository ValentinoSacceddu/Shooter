#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaPlayer(int y, int x) 
{
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    // Disegna giocatore
    mvprintw(y, x, "<0>");

    attroff(COLOR_PAIR(2));
    refresh();
}

void muoviPlayer(int *y, int *x, int key) 
{
    switch (key) 
    {
        case KEY_UP:
            if (*y > 1 && mvinch(*y - 1, *x) == ' ')
                *y -= 1;
            break;
        case KEY_DOWN:
            if (*y < ALTEZZA - 2 && mvinch(*y + 1, *x) == ' ')
                *y += 1;
            break;
        case KEY_LEFT:
            if (*x > 1 && mvinch(*y, *x - 1) == ' ')
                *x -= 1;
            break;
        case KEY_RIGHT:
            if (*x < LARGHEZZA - 4 && mvinch(*y, *x + 3) == ' ')
                *x += 1;
            break;
    }
}