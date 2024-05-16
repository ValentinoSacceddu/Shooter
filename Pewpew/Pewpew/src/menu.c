#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaMenu(int selected_option) {
    erase();
    attron(A_BOLD); // Testo in grassetto
    mvprintw(ALTEZZA / 2 - 1, LARGHEZZA / 2 - 4, "PEWPEW");
    attroff(A_BOLD);
    mvprintw(ALTEZZA / 2 + 1, LARGHEZZA / 2 - 3, "Proteggi la tua casa!");

    // Disegna le opzioni del menu
    mvprintw(ALTEZZA / 2 + 3, LARGHEZZA / 2 - 7, "  GIOCA");
    mvprintw(ALTEZZA / 2 + 4, LARGHEZZA / 2 - 7, "  PUNTEGGIO");
    mvprintw(ALTEZZA / 2 + 5, LARGHEZZA / 2 - 7, "  CARICA SALVATAGGIO");
    mvprintw(ALTEZZA / 2 + 6, LARGHEZZA / 2 - 7, "  INFO");

    // Colora di verde l'opzione selezionata
    attron(COLOR_PAIR(2)); // Verde
    switch(selected_option) {
        case 0:
            mvprintw(ALTEZZA / 2 + 3, LARGHEZZA / 2 - 7, "> GIOCA");
            break;
        case 1:
            mvprintw(ALTEZZA / 2 + 4, LARGHEZZA / 2 - 7, "> PUNTEGGIO");
            break;
        case 2:
            mvprintw(ALTEZZA / 2 + 5, LARGHEZZA / 2 - 7, "> CARICA SALVATAGGIO");
            break;
        case 3:
            mvprintw(ALTEZZA / 2 + 6, LARGHEZZA / 2 - 7, "> INFO");
            break;
    }
    attroff(COLOR_PAIR(2));

    refresh();
}