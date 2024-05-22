#ifndef ZOMBIE_H
#define ZOMBIE_H

typedef struct 
{
    int a;   
    int b;   
    int colpito; 
} Posizione;

void disegnaZombie(Posizione *posizioneZombie, int numZombie);

void generaPosizioniZombie(Posizione *posizioneZombie, int numZombie);

int controllaCollisioneZombie(Posizione zombiePos, Ostacolo *ostacoli, int numOstacoli);

void ruotaZombie(Posizione *zombiePos, int direzione);

void movimentoVersoTarget(Posizione *pos, Posizione target, Ostacolo *ostacoli, int numOstacoli);

void muoviZombie(Posizione *posizioneZombie, int numZombie, Posizione target);


void dannoZombie(Posizione *posizioneZombie);

#endif