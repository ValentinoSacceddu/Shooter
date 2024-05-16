#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaZombie(Posizione *zombie_positions, int num_zombies) {
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(6));

    for (int i = 0; i < num_zombies; ++i) {
        mvprintw(zombie_positions[i].a, zombie_positions[i].b, "<X>");
    }

    attroff(COLOR_PAIR(6));
    refresh();  
}

void generaPosizioniZombie(Posizione *zombie_positions, int num_zombies) {
    // Genera posizioni casuali per gli zombi nella parte superiore dello schermo
    for (int i = 0; i < num_zombies; ++i) {
        zombie_positions[i].a = 1; // Partono tutti dall'alto
        zombie_positions[i].b = rand() % (LARGHEZZA - 2) + 1; // Posizione casuale sull'asse orizzontale
    }
}

int controllaCollisioneZombie(Posizione zombie_pos, Ostacolo *ostacoli, int num_ostacoli) {
    for (int i = 0; i < num_ostacoli; ++i) {
        if (zombie_pos.a == ostacoli[i].y && zombie_pos.b == ostacoli[i].x) {
            return 1; // Collisione rilevata
        }
    }
    return 0; // Nessuna collisione
}

void ruotaZombie(Posizione *zombie_pos, int direction) {
    // Ruota lo zombie di 90 gradi in senso antiorario se direction = -1
    // Ruota lo zombie di 90 gradi in senso orario se direction = 1
    int tmp = zombie_pos->a;
    zombie_pos->a = zombie_pos->b * direction;
    zombie_pos->b = -tmp * direction;
}

void movimentoVersoTarget(Posizione *pos, Posizione target) {
    // Calcola differenza di posizioni tra posizione attuale e il target
    int dx = target.a - pos->a;
    int dy = target.b - pos->b;

    // Determina la direzione in cui muoversi
    int dirA = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;  // 1 se target a destra, -1 se a sinistra, 0 se sulla stessa colonna
    int dirB = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;  // 1 se target in basso, -1 se in alto, 0 se sulla stessa riga

    // Muovi verso il target
    pos->a += dirA;
    pos->b += dirB;
}

void muoviZombie(Posizione *zombie_positions, int num_zombies, Posizione target) {
    for (int i = 0; i < num_zombies; ++i) {
        movimentoVersoTarget(&zombie_positions[i], target);
    }
}