#include "librerie.h"

#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define ALTEZZA 35
#define LARGHEZZA 100
#define TIMEOUT_VALUE 100

int main() 
{
    int x = 50, y = 27, key, sparo = 0, HP = 10, j, k;
    int numOndate = 0;
    int numZombie = 5;
    int maxZombie = 15;

    Proiettile *listaProiettili = NULL;
    Posizione posizioneZombie[10];
    Ostacolo ostacoli[] = 
    {
        {10, 40}, {11, 40}, {12, 40}, {13, 40},
        {25, 90}, {26, 90}, {27, 90}, {28, 90},
        {17, 60}, {18, 60}, {19, 60}, {20, 60},
        {8, 5}, {9, 5}, {10, 5}, {11, 5}
    };
    
    int num_ostacoli = sizeof(ostacoli) / sizeof(Ostacolo);

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));
    timeout(TIMEOUT_VALUE);

    int scelta = 0;

    disegnaMenu(scelta);
    refresh();

    while ((key = getch()) != '\n') 
    {
        switch(key) 
        {
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

    erase();
    confini();
    disegnaOstacoli();
    disegnaCasa(20, 20);
    disegnaCasa(10, 80);
    disegnaCasaPlayer(30, 50);
    disegnaPlayer(y, x);
    //generaPosizioniZombie(zombie_positions, 10);

    int contatoreMovimento = 0;
    int frequenzaMovimento = 5;

    while ((key = getch()) != 'q') 
    {
        switch(key)
            {
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

        if (sparo) 
        {
            aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
            sparo = 0;
        }

        muoviProiettili(&listaProiettili, posizioneZombie, 10);
        disattivaProiettili(&listaProiettili, ALTEZZA, LARGHEZZA);

        if (contatoreMovimento % frequenzaMovimento == 0) 
        {
            numOndate++;
            if (numOndate == 2) 
            {
                numZombie = 10; // Seconda ondata: aumenta il numero di zombie
            } 
            else if (numOndate == 3) 
            {
                numZombie = 15; // Terza ondata: aumenta ulteriormente il numero di zombie
            }
            generaPosizioniZombie(posizioneZombie, numZombie);
        }

        erase();
        confini();
        disegnaOstacoli();
        disegnaCasa(20, 20);
        disegnaCasaPlayer(30, 50);
        disegnaCasa(10, 80);
        disegnaPlayer(y, x);
        disegnaProiettili(listaProiettili);
        disegnaZombie(posizioneZombie, 10);
        refresh();

        contatoreMovimento++;
        usleep(10000);
    }

    endwin();
    liberaListaProiettili(listaProiettili);

    return 0;
}
