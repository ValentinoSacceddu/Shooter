#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaZombie(Posizione *posizioneZombie, int numZombie, int *zombieColpito) 
{
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);  // Coppia di colori per zombie colpiti

    for (int i = 0; i < numZombie; ++i) 
    {
        if (zombieColpito[i]) {
            attron(COLOR_PAIR(7));
        } else {
            attron(COLOR_PAIR(6));
        }

        mvprintw(posizioneZombie[i].a, posizioneZombie[i].b, "<X>");

        if (zombieColpito[i]) {
            attroff(COLOR_PAIR(7));
        } else {
            attroff(COLOR_PAIR(6));
        }
    }

    refresh();  
}
void generaPosizioniZombie(Posizione *posizioneZombie, int numZombie)
{
    // Genera posizioni casuali per gli zombi nella parte superiore dello schermo
    for (int i = 0; i < numZombie; ++i) 
    {
        posizioneZombie[i].a = 1; // Partono tutti dall'alto
        posizioneZombie[i].b = rand() % (LARGHEZZA - 2) + 1; // Posizione casuale sull'asse orizzontale
    }
}

int controllaCollisioneZombie(Posizione posZombie, Ostacolo *ostacoli, int numOstacoli) 
{
    for (int i = 0; i < numOstacoli; ++i) 
    {
        if (posZombie.a == ostacoli[i].y && posZombie.b == ostacoli[i].x) 
        {
            return 1; // Collisione rilevata
        }
    }
    return 0; // Nessuna collisione
}
void gestisciCollisioni(Proiettile **listaProiettili, Posizione *posizioneZombie, int *numZombie) {
    Proiettile *tmp = *listaProiettili;
    while (tmp != NULL) {
        if (tmp->attivo) {
            for (int i = 0; i < *numZombie; ++i) {
                if (tmp->x == posizioneZombie[i].b && tmp->y == posizioneZombie[i].a) {
                    // Lo zombie è stato colpito
                    tmp->attivo = 0; // Disattiva il proiettile
                    // Rimuovi lo zombie colpito dalla lista delle posizioni degli zombie
                    for (int j = i; j < *numZombie - 1; ++j) {
                        posizioneZombie[j] = posizioneZombie[j + 1];
                    }
                    (*numZombie)--; // Decrementa il numero di zombie
                }
            }
        }
        tmp = tmp->next;
    }
}

void ruotaZombie(Posizione *posZombie, int direzione) 
{
    // Ruota lo zombie di 90 gradi in senso antiorario se direction = -1
    // Ruota lo zombie di 90 gradi in senso orario se direction = 1
    int tmp = posZombie->a;
    posZombie->a = posZombie->b * direzione;
    posZombie->b = -tmp * direzione;
}

void movimentoVersoTarget(Posizione *pos, Posizione target) 
{
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

void muoviZombie(Posizione *posizioneZombie, int numZombie, Posizione target) 
{
    for (int i = 0; i < numZombie; ++i) 
    {
        movimentoVersoTarget(&posizioneZombie[i], target);
    }
}

int controllaColpoZombie(Posizione *posizioneZombie, Proiettile *proiettili) 
{
    int numZombie;
    while (proiettili != NULL) 
    {
        for (int i = 0; i < numZombie; ++i) 
        {
            if (proiettili->x == posizioneZombie[i].b && proiettili->y == posizioneZombie[i].a) 
            {
                // Lo zombie è stato colpito
                return i; // Restituisci l'indice dello zombie colpito
            }
        }
        proiettili = proiettili->next;
    }
    return -1; 
}