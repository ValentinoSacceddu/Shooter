#include "librerie.h"
#define ALTEZZA 35
#define LARGHEZZA 100
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define TIMEOUT_VALUE 100 


// Funzione per creare un nuovo proiettile
Proiettile* creaProiettile(int x, int y, int dx, int dy) {
    Proiettile *p = malloc(sizeof(Proiettile));
    p->x = x;
    p->y = y;
    p->dx = dx;
    p->dy = dy;
    p->attivo = 1;
    p->next = NULL;
    return p;
}

// Funzione per aggiungere un nuovo proiettile alla lista
void aggiungiProiettile(Proiettile **lista, Proiettile *p) {
    if (*lista == NULL) {
        *lista = p;
    } else {
        Proiettile *tmp = *lista;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = p;
    }
}

// Funzione per disattivare i proiettili che escono dalla finestra
void disattivaProiettili(Proiettile **lista, int altezza_f, int larghezza_f) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->x < 0 || tmp->x >= larghezza_f || tmp->y < 0 || tmp->y >= altezza_f) {
            tmp->attivo = 0;
        }
        tmp = tmp->next;
    }
}


// Funzione per muovere i proiettili
void muoviProiettili(Proiettile **lista) {
    Proiettile *tmp = *lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            // Aggiorna la posizione del proiettile
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;

            // Verifica se il proiettile ha colpito un ostacolo
            if (mvinch(tmp->y, tmp->x) != ' ') {
                tmp->attivo = 0; // Disattiva il proiettile
            }
        }
        tmp = tmp->next;
    }
}


// Funzione per disegnare i proiettili
void disegnaProiettili(Proiettile *lista) {
    Proiettile *tmp = lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            mvprintw(tmp->y, tmp->x, " %c", PROIETTILE_CHAR);
        }
        tmp = tmp->next;
    }
}

// Funzione per liberare la memoria allocata per la lista dei proiettili
void liberaListaProiettili(Proiettile *lista) {
    Proiettile *tmp;
    while (lista != NULL) {
        tmp = lista;
        lista = lista->next;
        free(tmp);
    }
}