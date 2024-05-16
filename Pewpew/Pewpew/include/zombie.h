#ifndef ZOMBIE_H
#define ZOMBIE_H

typedef struct 
{
    int a;
    int b;
} Posizione;

void disegnaZombie(Posizione *zombie_positions, int num_zombies);

void generaPosizioniZombie(Posizione *zombie_positions, int num_zombies);

int controllaCollisioneZombie(Posizione zombie_pos, Ostacolo *ostacoli, int num_ostacoli);

void ruotaZombie(Posizione *zombie_pos, int direction);

void movimentoVersoTarget(Posizione *pos, Posizione target);

void muoviZombie(Posizione *zombie_positions, int num_zombies, Posizione target);

#endif