#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define ALTEZZA 35
#define LARGHEZZA 100

// Struttura per il proiettile
typedef struct Proiettile {
    int x;
    int y;
    int dx;
    int dy;
    int attivo;
    struct Proiettile *next;
} Proiettile;

// Funzione per creare un nuovo proiettile
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

// Funzione per aggiungere un nuovo proiettile alla lista
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

// Funzione per disattivare i proiettili che escono dalla finestra
void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->x < 0 || tmp->x >= larghezza_f || tmp->y < 0 || tmp->y >= altezza_f) {
            tmp->attivo = 0;
        }
        tmp = tmp->next;
    }
}

// Funzione per muovere i proiettili
void muoviProiettili(Proiettile **lista) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;
        }
        tmp = tmp->next;
    }
}

// Funzione per disegnare i proiettili
void disegnaProiettili(Proiettile *lista) {
    Proiettile *tmp = lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            mvprintw(tmp->y, tmp->x, "%c", PROIETTILE_CHAR);
        }
        tmp = tmp->next;
    }
}

// Funzione per liberare la memoria allocata per la lista dei proiettili
void liberaListaProiettili(Proiettile *lista) {
    Proiettile *tmp;
    while (lista != NULL) {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}

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

void disegnaOstacoli() 
{
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(1));
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
    attroff(COLOR_PAIR(1));

    refresh();
}

void disegnaCasa(int start_y, int start_x) 
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

void disegnaPlayer(int y, int x) 
{
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(3));

    // Disegna giocatore
    mvprintw(y, x, "|O|");

    attroff(COLOR_PAIR(3));
    refresh();
}

void muoviPlayer(int *y, int *x, int key)
{
    // Movimento giocatore in base all'input della tastiera
    switch (key) {
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

int main() 
{
    int x = 5, y = 17, key, sparo = 0;
    Proiettile *listaProiettili = NULL;
    initscr(); // Inizializzazione ncurses
    start_color();
    cbreak();  // Disabilita buffering
    noecho();  // Disabilita la stampa degli input del giocatore
    keypad(stdscr, TRUE); // Attiva le frecce direzionali
    curs_set(0); // nascondi il cursore

    // Disegna confini ed ostacoli
    confini();
    disegnaOstacoli();
    disegnaCasa(20, 20);
    disegnaCasa(30, 50);
    disegnaCasa(10, 80);

    disegnaPlayer(y, x);

    // Ciclo per far muovere il giocatore
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

        // Con la barra spaziatrice si spara
        if (sparo) 
        {
            aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
        }

        // Muovi proiettili
        muoviProiettili(&listaProiettili);

        // Disabilita i proiettili che vanno oltre i confini della finestra
        disattivaProiettili(&listaProiettili, ALTEZZA, LARGHEZZA);

        erase(); // Pulisci lo schermo
        confini();
        disegnaOstacoli();
        disegnaCasa(20, 20);
        disegnaCasa(30, 50);
        disegnaCasa(10, 80);
        disegnaPlayer(y, x);
        disegnaProiettili(listaProiettili);
        refresh(); // Aggiorna la finestra
    }

    // Fine modalità Ncurses
    endwin();

    // libera la memoria allocata ai proiettili
    liberaListaProiettili(listaProiettili);

    return 0;
}
