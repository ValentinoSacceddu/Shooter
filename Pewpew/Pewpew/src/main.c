#include "librerie.h"

#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define ALTEZZA 35
#define LARGHEZZA 100
#define TIMEOUT_VALUE 100

int main() 
{
    int x = 50, y = 27, key, sparo = 0, HP = 10, j, k;
    Proiettile *listaProiettili = NULL;
    Posizione zombie_positions[10];
    //Posizione cpuPosizione = {10, 10};  //Posizione iniziale CPU
    //Posizione target = {20, 20};       // Posizione target
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));
    timeout(TIMEOUT_VALUE); // Imposta il timeout per la lettura dell'input

    int scelta = 0;

    // Disegna il menu iniziale
    disegnaMenu(scelta);
    refresh();

    // Attendi l'input dell'utente per iniziare il gioco
    while ((key = getch()) != '\n') {
        switch(key) {
            case KEY_UP:
                scelta = (scelta - 1 < 0) ? 0 : scelta - 1;
                break;
            case KEY_DOWN:
                scelta = (scelta + 1 > 3) ? 3 : scelta + 1;
                break;
        }
        disegnaMenu(scelta);
        refresh();
    }

    // Pulisci lo schermo e inizia il gioco
    erase();
    confini();
    disegnaOstacoli();
    disegnaCasa(20, 20);
    disegnaCasa(10, 80);
    disegnaCasaPlayer(30, 50);
    disegnaPlayer(y, x);
    generaPosizioniZombie(zombie_positions, 10);

    int zombie_move_counter = 0;
    int zombie_move_frequency = 5; // Modifica la frequenza del movimento degli zombi come preferisci

    while ((key = getch()) != 'q') 
    {
        // Gestione degli input
        switch(key) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                muoviPlayer(&y, &x, key);
                break;
            case ' ':
                sparo = 1;
                break;
        }

        // Movimento dei proiettili
        if (sparo) 
        {
            aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
            sparo = 0; // Resetta lo stato di sparo dopo aver sparato
        }
       //moveTowardsTarget(&cpuPosition, target);
        muoviProiettili(&listaProiettili);
        disattivaProiettili(&listaProiettili, ALTEZZA, LARGHEZZA);

        // Movimento degli zombi solo ogni tot iterazioni
        if (zombie_move_counter % zombie_move_frequency == 0) {
            muoviZombie(zombie_positions, 10, (Posizione){30, 50}); // Passa la posizione della casa blu come target
        }

        erase();
        confini();
        disegnaOstacoli();
        disegnaCasa(20, 20);
        disegnaCasaPlayer(30, 50);
        disegnaCasa(10, 80);
        disegnaPlayer(y, x);
        disegnaProiettili(listaProiettili);
        disegnaZombie(zombie_positions, 10);
        HPcasa(HP, j, k);
        refresh();
        // Incrementa il contatore di movimento degli zombi
        zombie_move_counter++;

        // Pausa per un breve intervallo prima del prossimo ciclo
        usleep(10000); // Pausa di 0.01 secondi
    }


    endwin();
    liberaListaProiettili(listaProiettili);

    return 0;
}
