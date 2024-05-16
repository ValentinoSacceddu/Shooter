#ifndef OSTACOLI_H
#define OSTACOLI_H
  
typedef struct Ostacolo{
    int y;
    int x;
} Ostacolo;

void disegnaOstacoli();

void disegnaCasa(int start_y, int start_x);

void disegnaCasaPlayer(int start_y, int start_x);

#endif