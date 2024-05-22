#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

void disegnaZombie(Posizione *posizioneZombie, int numZombie) 
{
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(6));

    for (int i = 0; i < numZombie; ++i) 
    {
        if (!posizioneZombie[i].colpito) 
        {
            mvprintw(posizioneZombie[i].a, posizioneZombie[i].b, "<X>");
        }
    }

    attroff(COLOR_PAIR(6));
    refresh();  
}



int controllaCollisioneZombie(Posizione zombiePos, Ostacolo *ostacoli, int numOstacoli) 
{
    for (int i = 0; i < numOstacoli; ++i) 
    {
        if (zombiePos.a == ostacoli[i].y && zombiePos.b == ostacoli[i].x) 
        {
            return 1; // Collisione rilevata
        }
    }
    return 0; // Nessuna collisione
}

void ruotaZombie(Posizione *zombiePos, int direzione) 
{
    // Ruota lo zombie di 90 gradi in senso antiorario se direction = -1
    // Ruota lo zombie di 90 gradi in senso orario se direction = 1
    int tmp = zombiePos->a;
    zombiePos->a = zombiePos->b * direzione;
    zombiePos->b = -tmp * direzione;
}

void movimentoVersoTarget(Posizione *pos, Posizione target, Ostacolo *ostacoli, int numOstacoli) 
{
    int dx = target.a - pos->a;
    int dy = target.b - pos->b;
    int dirA = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int dirB = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    Posizione newPos = *pos;

    newPos.a += dirA;
    if (!controllaCollisioneZombie(newPos, ostacoli, numOstacoli))
    {
        pos->a = newPos.a;
    } 
    else 
    {
        newPos.a -= dirA;
    }

    newPos.b += dirB;
    if (!controllaCollisioneZombie(newPos, ostacoli, numOstacoli)) 
    {
        pos->b = newPos.b;
    }
}

void muoviZombie(Posizione *posizioneZombie, int numZombie, Posizione target) 
{
    // Aggiorna la posizione di ciascuno zombie verso il bersaglio (la casa)
    for (int i = 0; i < numZombie; ++i) 
    {
        int dx = target.a - posizioneZombie[i].a;
        int dy = target.b - posizioneZombie[i].b;
        int dirA = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        int dirB = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

        Posizione newPos = posizioneZombie[i];

        newPos.a += dirA;
        posizioneZombie[i].a = newPos.a;

        newPos.b += dirB;
        posizioneZombie[i].b = newPos.b;
    }
}



void generaPosizioniZombie(Posizione *posizioneZombie, int numZombie)
{
    // Genera posizioni casuali per gli zombi sugli estremi della mappa
    for (int i = 0; i < numZombie; ++i) 
    {
                posizioneZombie[i].a = 1;
                posizioneZombie[i].b = rand() % (LARGHEZZA - 2) + 1; // Posizione casuale sull'asse orizzontale

    }
}
