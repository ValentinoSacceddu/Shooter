#include "librerie.h"

#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 

Proiettile* creaProiettile(int x, int y, int dx, int dy) 
{
    Proiettile *p = malloc(sizeof(Proiettile));
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->attivo = 1;
    p->next = NULL;
    return p;
}

void aggiungiProiettile(Proiettile **lista, Proiettile *p) 
{
    if (*lista == NULL) 
    {
        *lista = p;
    } else {
        Proiettile *tmp = *lista;
        while (tmp->next != NULL) 
        {
            tmp = tmp->next;
        }
        tmp->next = p;
    }
}

void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f) 
{
    Proiettile *tmp = *lista;
    while (tmp != NULL) 
    {
        if (tmp->x < 0 || tmp->x >= larghezza_f || tmp->y < 0 || tmp->y >= altezza_f) 
        {
            tmp->attivo = 0;
        }
        tmp = tmp->next;
    }
}

void muoviProiettili(Proiettile **lista, Posizione *posizioneZombie, int numZombie) 
{
    Proiettile *tmp = *lista;
    while (tmp != NULL) 
    {
        if (tmp->attivo) 
        {
            // Aggiorna la posizione del proiettile
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;

            // Verifica se il proiettile ha colpito un ostacolo o uno zombie
            if (mvinch(tmp->y, tmp->x) != ' ') 
            {
                tmp->attivo = 0; // Disattiva il proiettile
            }

            // Controlla collisione con gli zombi
            for (int i = 0; i < numZombie; ++i) 
            {
                if (posizioneZombie[i].a == tmp->y && posizioneZombie[i].b == tmp->x && !posizioneZombie[i].colpito) 
                {
                    posizioneZombie[i].colpito = 1; // Segna lo zombie come colpito
                    tmp->attivo = 0; // Disattiva il proiettile
                    break;
                }
            }
        }
        tmp = tmp->next;
    }
}

void disegnaProiettili(Proiettile *lista) 
{
    Proiettile *tmp = lista;
    while (tmp != NULL) 
    {
        if (tmp->attivo) 
        {
            mvprintw(tmp->y, tmp->x, " %c", PROIETTILE_CHAR);
        }
        tmp = tmp->next;
    }
}

void liberaListaProiettili(Proiettile *lista) 
{
    Proiettile *tmp;
    while (lista != NULL) 
    {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}
