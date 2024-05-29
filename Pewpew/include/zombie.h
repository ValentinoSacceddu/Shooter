#include "proiettili.h"

#ifndef ZOMBIE_H
#define ZOMBIE_H


void disegnaZombie(Posizione *posizioneZombie, int numZombie, int *zombieColpito);

void generaPosizioniZombie(Posizione *posizioneZombie, int numZombie);

void ruotaZombie(Posizione *zombiePos, int direzione);

void movimentoVersoTarget(Posizione *pos, Posizione target);

void muoviZombie(Posizione *posizioneZombie, int numZombie, Posizione target);

void dannoZombie(Posizione *posizioneZombie);

int controllaColpoZombie(Posizione *posizioneZombie, Proiettile *proiettili);

void gestisciCollisioni(Proiettile **listaProiettili, Posizione *posizioneZombie, int *numZombie);


#endif