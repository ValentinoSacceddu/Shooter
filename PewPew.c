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

typedef struct 
{
    int a;
    int b;
} Posizione;

typedef struct {
    int x_giocatore;
    int y_giocatore;
    int HP_casa;
} StatoGioco;

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

/*void muoviZombie(Posizione *cpu, Posizione target) 
{
    // Calcola differenza di posizioni tra CPU e target
    int dx = target.x - cpu->x;
    int dy = target.y - cpu->y;

    // Determina la direzione in cui muoversi
    int dirX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;  // 1 se target a destra, -1 se a sinstra, 0 se sulla stessa colonna
    int dirY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;  // 1 se target in basso, -1 se in alto, 0 se sulla stessa riga

    // Muovi CPU verso il target
    cpu->x += dirX;
    cpu->y += dirY;
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

void HPcasa(int HP, int j, int k){
    /*while(HP > 0){
        disegnaZombie(j, k);
       if (j == 50 || (j == 51 || (j == 52 || (j == 53 || (j == 54 || (j == 55 || (j == 56 || (j == 57 || (j == 58 || (j == 59 || (j == 60 || (k == 33 || (k == 32 || (k == 31 || (k == 30 || (k == 29 || (k == 28 || (k ==27 || (k == 26)))))))))))))))))));
           HP--;
    }
*/
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

      

StatoGioco memorizzaStatoGioco(int x_giocatore, int y_giocatore, int HP_casa) {
    StatoGioco stato;
    stato.x_giocatore = x_giocatore;
    stato.y_giocatore = y_giocatore;
    stato.HP_casa = HP_casa;
    return stato;
}

/*void ripristinaStatoGioco(StatoGioco stato) {
    x = stato.x_giocatore;
    y = stato.y_giocatore;
    HP = stato.HP_casa;
}
*/
int main() 
{
    int x = 50, y = 27, key, sparo = 0, HP = 10, j, k;
    Proiettile *listaProiettili = NULL;
    //Posizione cpuPosizione = {10, 10};  //Posizione iniziale CPU
    //Posizione target = {20, 20};       // Posizione target
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    timeout(TIMEOUT_VALUE); // Imposta il timeout per la lettura dell'input

    int scelta = 0;

    // Disegna il menu iniziale
    disegnaMenu(scelta);
    refresh();

    // Attendi l'input dell'utente per iniziare il gioco
    while ((key = getch()) != '\n') {
        switch(key) {
            case KEY_UP:
                scelta = (scelta - 1 < 0) ? 0 : scelta - 1;
                break;
            case KEY_DOWN:
                scelta = (scelta + 1 > 3) ? 3 : scelta + 1;
                break;
        }
        disegnaMenu(scelta);
        refresh();
    }

    // Pulisci lo schermo e inizia il gioco
    erase();
    confini();
    disegnaOstacoli();
    disegnaCasa(20, 20);
    disegnaCasa(10, 80);
    disegnaCasaPlayer(30, 50);
    disegnaPlayer(y, x);

    StatoGioco stato_iniziale = memorizzaStatoGioco(x, y, HP);

    while ((key = getch()) != 'q') 
    {
        // Gestione degli input
        switch(key) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                muoviPlayer(&y, &x, key);
                break;
            case ' ':
                sparo = 1;
                break;
        }

        // Movimento dei proiettili
        if (sparo) 
        {
            aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
            sparo = 0; // Resetta lo stato di sparo dopo aver sparato
        }
       //moveTowardsTarget(&cpuPosition, target);
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
        HPcasa(HP, j, k);
    }

    endwin();
    liberaListaProiettili(listaProiettili);

    return 0;
}
