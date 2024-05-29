#ifndef PROIETTILI_H
#define PROIETTILI_H

typedef struct 
{
    int a;   
    int b;   
    int colpito; 
    int attivo;
} Posizione;

typedef struct Proiettile {
    int x;
    int y;
    int dx;
    int dy;
    int attivo;
    struct Proiettile *next;
} Proiettile;


Proiettile* creaProiettile(int x, int y, int dx, int dy);
void aggiungiProiettile(Proiettile **lista, Proiettile *p);
void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f);
void muoviProiettili(Proiettile **lista, Posizione *posizioneZombie, int *numZombie, int *zombieColpito);
void disegnaProiettili(Proiettile *lista);
void liberaListaProiettili(Proiettile *lista);

#endif