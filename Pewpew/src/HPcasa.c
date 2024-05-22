#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void HPcasa(int HP, int j, int k)
{
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    mvprintw(36, 2, "HP CASA:");
    if (HP==10){
        mvprintw(36, 10, "||||||||||");
    }
    if (HP==9){
        mvprintw(36, 10, "|||||||||");
        }
    if (HP==8){
        mvprintw(36, 10, "||||||||");
    }
    if (HP==7){
        mvprintw(36, 10, "|||||||");
    }
    if (HP==6){
        mvprintw(36, 10, "||||||");
    }
    if (HP==5){
        mvprintw(36, 10, "|||||");
    }
    if (HP==4){
        mvprintw(36, 10, "||||");
    }
    if (HP==3){
        mvprintw(36, 10, "|||");
    }
    if (HP==2){
        mvprintw(36, 10, "||");
    }
    if (HP==1){
        mvprintw(36, 10, "|");
    }
    if (HP==0){
        attron(COLOR_PAIR(7));
        attron(A_BOLD);
        mvprintw(17, 45, "GAME OVER");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(7));
    }
}
