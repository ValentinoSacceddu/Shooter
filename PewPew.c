#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h> 

#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define ALTEZZA 35
#define LARGHEZZA 100
#define TIMEOUT_VALUE 100 // Timeout in millisecondi (0.1 secondo)

typedef struct Proiettile {
    int x;
    int y;
    int dx;
    int dy;
    int attivo;
    struct Proiettile *next;
} Proiettile;

Proiettile* creaProiettile(int x, int y, int dx, int dy) {
    Proiettile *p = malloc(sizeof(Proiettile));
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->attivo = 1;
    p->next = NULL;
    return p;
}

void aggiungiProiettile(Proiettile **lista, Proiettile *p) {
    if (*lista == NULL) {
        *lista = p;
    } else {
        Proiettile *tmp = *lista;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = p;
    }
}

void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->x < 0 || tmp->x >= larghezza_f || tmp->y < 0 || tmp->y >= altezza_f) {
            tmp->attivo = 0;
        }
        tmp = tmp->next;
    }
}

void muoviProiettili(Proiettile **lista) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;

            if (mvinch(tmp->y, tmp->x) != ' ') {
                tmp->attivo = 0;
            }
        }
        tmp = tmp->next;
    }
}

void disegnaProiettili(Proiettile *lista) {
    Proiettile *tmp = lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            mvprintw(tmp->y, tmp->x, " %c", PROIETTILE_CHAR);
        }
        tmp = tmp->next;
    }
}

void liberaListaProiettili(Proiettile *lista) {
    Proiettile *tmp;
    while (lista != NULL) {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}

void disegnaMenu() {
    attron(A_BOLD); // Testo in grassetto
    mvprintw(ALTEZZA / 2 - 1, LARGHEZZA / 2 - 4, "PEWPEW");
    attroff(A_BOLD);
    mvprintw(ALTEZZA / 2 + 1, LARGHEZZA / 2 - 3, "Gioca");
}

void confini() {
    int i;
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (i = 0; i < LARGHEZZA; i++) {
        mvaddch(0, i, '=');
        mvaddch(ALTEZZA - 1, i, '=');
    }
    for (i = 0; i < ALTEZZA; i++) {
        mvaddch(i, 0, '[');
        mvaddch(i, LARGHEZZA - 1, ']');
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

void disegnaOstacoli() {
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


    mvprintw(8, 5, "/////////");
    mvprintw(9, 5, "/////////");
    mvprintw(10, 5, "/////////");
    mvprintw(11, 5, "/////////");
    attroff(COLOR_PAIR(4));

    refresh();
}

void disegnaCasa(int start_y, int start_x) {
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(5));

    mvprintw(start_y - 1 , start_x , "   /\\");
    mvprintw(start_y, start_x + 1, " /  \\ ");
    mvprintw(start_y + 1, start_x + 1, "/    \\");
    mvprintw(start_y - 1, start_x + 7, "    \\");
    mvprintw(start_y, start_x + 8, "    \\");
    mvprintw(start_y + 1, start_x + 8, "     \\");
    mvprintw(start_y - 2, start_x + 4, "_______");
    mvprintw(start_y + 1, start_x + 2, "____");
    mvprintw(start_y + 1, start_x + 7, "______");

    mvprintw(start_y + 2, start_x + 6, "|");
    mvprintw(start_y + 3, start_x + 6, "|");
    mvprintw(start_y + 2, start_x + 1, "|");
    mvprintw(start_y + 3, start_x + 1, "|");
    mvprintw(start_y + 2, start_x + 13, "|");
    mvprintw(start_y + 3, start_x + 13, "|");

    mvprintw(start_y + 3, start_x + 2, "____");
    mvprintw(start_y + 3, start_x + 7, "______");

    mvprintw(start_y + 2, start_x + 3, "[]");
    mvprintw(start_y + 2, start_x + 8, "[][]");

    attroff(COLOR_PAIR(5));
    refresh();
}

void disegnaCasaPlayer(int start_y, int start_x) {
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    mvprintw(start_y - 1 , start_x , "   /\\");
    mvprintw(start_y, start_x + 1, " /  \\ ");
    mvprintw(start_y + 1, start_x + 1, "/    \\");
    mvprintw(start_y - 1, start_x + 7, "    \\");
    mvprintw(start_y, start_x + 8, "    \\");
    mvprintw(start_y + 1, start_x + 8, "     \\");
    mvprintw(start_y - 2, start_x + 4, "_______");
    mvprintw(start_y + 1, start_x + 2, "____");
    mvprintw(start_y + 1, start_x + 7, "______");

    mvprintw(start_y + 2, start_x + 6, "|");
    mvprintw(start_y + 3, start_x + 6, "|");
    mvprintw(start_y + 2, start_x + 1, "|");
    mvprintw(start_y + 3, start_x + 1, "|");
    mvprintw(start_y + 2, start_x + 13, "|");
    mvprintw(start_y + 3, start_x + 13, "|");

    mvprintw(start_y + 3, start_x + 2, "____");
    mvprintw(start_y + 3, start_x + 7, "______");

    mvprintw(start_y + 2, start_x + 3, "[]");
    mvprintw(start_y + 2, start_x + 8, "[][]");

    attroff(COLOR_PAIR(2));
    refresh();
}

void disegnaPlayer(int y, int x) {
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    mvprintw(y, x, "<0>");

    attroff(COLOR_PAIR(2));
    refresh();
}

void disegnaZombie(int j, int k){
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(6));

    mvprintw(j, k, "<X>");

    attroff(COLOR_PAIR(6));
    refresh();  
}

/*void muoviZombie()
{
    srand(time(NULL));
    int i, direzione;
    direzione = rand() % 2 == 0 ? -1 : 1;
}
*/
void muoviPlayer(int *y, int *x, int key) {
    switch (key) {
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

void HPcasa(int HP){
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    mvprintw(36, 2, "HP:");
    if (HP==10){
        mvprintw(36, 5, "||||||||||");
    }
    if (HP==9){
        mvprintw(3, 5, "|||||||||");
        }
    if (HP==8){
        mvprintw(36, 5, "||||||||");
    }
    if (HP==7){
        mvprintw(36, 5, "|||||||");
    }
    if (HP==6){
        mvprintw(36, 5, "||||||");
    }
    if (HP==5){
        mvprintw(36, 5, "|||||");
    }
    if (HP==4){
        mvprintw(40, 55, "||||");
    }
    if (HP==3){
        mvprintw(40, 55, "|||");
    }
    if (HP==2){
        mvprintw(40, 55, "||");
    }
    if (HP==1){
        mvprintw(40, 55, "|");
    }
    if (HP==0){
        mvprintw(40, 55, "GAME OVER");
    }
}

int main() 
    {
    int x = 50, y = 27, key, sparo = 0, HP = 10;
    Proiettile *listaProiettili = NULL;
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    timeout(TIMEOUT_VALUE); // Imposta il timeout per la lettura dell'input

    // Disegna il menu iniziale
    disegnaMenu();
    refresh();

    // Attendi l'input dell'utente per iniziare il gioco
    getch();

    // Pulisci lo schermo e inizia il gioco
    erase();
    confini();
    disegnaOstacoli();
    disegnaCasa(20, 20);
    disegnaCasa(10, 80);
    disegnaCasaPlayer(30, 50);
    disegnaPlayer(y, x);

    while ((key = getch()) != 'q') 
    {
        muoviPlayer(&y, &x, key);
        if (key == ' ') 
        {
            sparo = 1;
        } 
        else 
        {
            sparo = 0;
        }

        if (sparo) 
        {
            aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
        }

        muoviProiettili(&listaProiettili);
        disattivaProiettili(&listaProiettili, ALTEZZA, LARGHEZZA);

        erase();
        confini();
        disegnaOstacoli();
        disegnaCasa(20, 20);
        disegnaCasaPlayer(30, 50);
        disegnaCasa(10, 80);
        disegnaPlayer(y, x);
        disegnaProiettili(listaProiettili);
        disegnaZombie(2, 50);
        HPcasa(HP);
    }

    endwin();
    liberaListaProiettili(listaProiettili);

    return 0;
}
