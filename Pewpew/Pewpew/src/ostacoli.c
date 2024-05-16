#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaOstacoli() 
{
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    mvprintw(10, 40, "/////////");
    mvprintw(11, 40, "/////////");
    mvprintw(12, 40, "/////////");
    mvprintw(13, 40, "/////////");

    mvprintw(25, 90, "/////////");
    mvprintw(26, 90, "/////////");
    mvprintw(27, 90, "/////////");
    mvprintw(28, 90, "/////////");

    mvprintw(17, 60, "/////////");
    mvprintw(18, 60, "/////////");
    mvprintw(19, 60, "/////////");
    mvprintw(20, 60, "/////////");

    mvprintw(3, 10, "///////////////");

    mvprintw(6, 10, "///");
    mvprintw(7, 10, "///");
    mvprintw(8, 10, "///");
    mvprintw(9, 10, "///");
    mvprintw(10, 10, "///");
    mvprintw(11, 10, "///");

    mvprintw(15, 5, "/////////");
    mvprintw(16, 5, "      ///");
    mvprintw(17, 5, "      ///");
    mvprintw(18, 5, "      ///");
    mvprintw(19, 5, "/////////");
    attroff(COLOR_PAIR(4));

    refresh();
}

void disegnaCasa(int start_y, int start_x) 
{
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(5));

    // Tetto
    mvprintw(start_y - 1 , start_x , "   /\\");
    mvprintw(start_y, start_x + 1, " /  \\ ");
    mvprintw(start_y + 1, start_x + 1, "/    \\");
    mvprintw(start_y - 1, start_x + 7, "    \\");
    mvprintw(start_y, start_x + 8, "    \\");
    mvprintw(start_y + 1, start_x + 8, "     \\");
    mvprintw(start_y - 2, start_x + 4, "_______");
    mvprintw(start_y + 1, start_x + 2, "____");
    mvprintw(start_y + 1, start_x + 7, "______");

    // Muri
    mvprintw(start_y + 2, start_x + 6, "|");
    mvprintw(start_y + 3, start_x + 6, "|");
    mvprintw(start_y + 2, start_x + 1, "|");
    mvprintw(start_y + 3, start_x + 1, "|");
    mvprintw(start_y + 2, start_x + 13, "|");
    mvprintw(start_y + 3, start_x + 13, "|");

    // Base
    mvprintw(start_y + 3, start_x + 2, "____");
    mvprintw(start_y + 3, start_x + 7, "______");

    // Finestre
    mvprintw(start_y + 2, start_x + 3, "[]");
    mvprintw(start_y + 2, start_x + 8, "[][]");

    attroff(COLOR_PAIR(5));
    refresh();
}

void disegnaCasaPlayer(int start_y, int start_x) 
{
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    // Tetto
    mvprintw(start_y - 1 , start_x , "   /\\");
    mvprintw(start_y, start_x + 1, " /  \\ ");
    mvprintw(start_y + 1, start_x + 1, "/    \\");
    mvprintw(start_y - 1, start_x + 7, "    \\");
    mvprintw(start_y, start_x + 8, "    \\");
    mvprintw(start_y + 1, start_x + 8, "     \\");
    mvprintw(start_y - 2, start_x + 4, "_______");
    mvprintw(start_y + 1, start_x + 2, "____");
    mvprintw(start_y + 1, start_x + 7, "______");

    // Muri
    mvprintw(start_y + 2, start_x + 6, "|");
    mvprintw(start_y + 3, start_x + 6, "|");
    mvprintw(start_y + 2, start_x + 1, "|");
    mvprintw(start_y + 3, start_x + 1, "|");
    mvprintw(start_y + 2, start_x + 13, "|");
    mvprintw(start_y + 3, start_x + 13, "|");

    // Base
    mvprintw(start_y + 3, start_x + 2, "____");
    mvprintw(start_y + 3, start_x + 7, "______");

    // Finestre
    mvprintw(start_y + 2, start_x + 3, "[]");
    mvprintw(start_y + 2, start_x + 8, "[][]");

    attroff(COLOR_PAIR(2));
    refresh();
}