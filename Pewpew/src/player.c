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
    // Movimento giocatore in base all'input della tastiera
    switch (key) 
    {
        case KEY_UP:
            if (*y > 1) // Blocca il movimento del giocatore oltre il confine superiore
                *y -= 1;
            break;
        case KEY_DOWN:
            if (*y < ALTEZZA - 2) // Blocca il movimento del giocatore oltre il confine inferiore
                *y += 1;
            break;
        case KEY_LEFT:
            if (*x > 1) // Blocca il movimento del giocatore oltre il confine di sinistra
                *x -= 1;
            break;
        case KEY_RIGHT:
            if (*x < LARGHEZZA - 4) // Blocca il movimento del giocatore oltre il confine di destra
                *x += 1;
            break;
    }
}