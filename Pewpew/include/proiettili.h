#ifndef PROIETTILI_H
#define PROIETTILI_H

#include <ncurses.h>
#include <stdlib.h>
#include "librerie.h"

typedef struct Proiettile 
{
    int x, y;
    int dx, dy;
    int attivo;
    struct Proiettile *next;
} Proiettile;

Proiettile* creaProiettile(int x, int y, int dx, int dy);

void aggiungiProiettile(Proiettile **lista, Proiettile *p);

void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f);

void muoviProiettili(Proiettile **lista, Posizione *posizioneZombie, int numZombie);

void disegnaProiettili(Proiettile *lista);

void liberaListaProiettili(Proiettile *lista);

#endif