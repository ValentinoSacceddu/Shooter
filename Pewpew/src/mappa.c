#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100

void confini() 
{
    int i;
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    // Disegna confini della mappa
    for (i = 0; i < LARGHEZZA; i++) 
    {
        mvaddch(0, i, '=');
        mvaddch(ALTEZZA - 1, i, '=');
    }
    for (i = 0; i < ALTEZZA; i++) 
    {
        mvaddch(i, 0, '[');
        mvaddch(i, LARGHEZZA - 1, ']');
    }
    attroff(COLOR_PAIR(1));
    refresh();
}