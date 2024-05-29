#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100

void mostraInfoOndata(int ondata, int numZombie)
{
    char messaggio[50];
    sprintf(messaggio, "Ondata %d - Zombie da uccidere: %d", ondata, numZombie);
    mvprintw(ALTEZZA / 2, (LARGHEZZA - strlen(messaggio)) / 2, "%s", messaggio);
    refresh();
    while (getch() == ERR);
}

void mostraVittoria()
{
    char messaggio[] = "HAI VINTO!";
    mvprintw(ALTEZZA / 2, (LARGHEZZA - strlen(messaggio)) / 2, "%s", messaggio);
    refresh();
    usleep(2000000);
}