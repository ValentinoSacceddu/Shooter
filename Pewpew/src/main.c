#include "librerie.h"
#define PROIETTILE_CHAR '|'
#define VELOCITA_PROIETTILE 1
#define ALTEZZA 35
#define LARGHEZZA 100
#define TIMEOUT_VALUE 100


    int main() 
    {
        int x = 50, y = 27, key, sparo = 0, HP = 10, j, k;
        int HPcasa = 100; 
        Proiettile *listaProiettili = NULL;
        Posizione posizioneZombie[20];
        int zombieColpito[20] = {0};  // Array per tenere traccia degli zombie colpiti
        int numZombie = 0;
        int ondata = 0;
        int ondate[] = {5, 10, 15};  // Numero di zombie per ogni ondata
        int numOndate = sizeof(ondate) / sizeof(ondate[0]);
        int ondataIniziata = 0;
        int contatoreMovimento = 0;
        int frequenzaMovimento = 5;

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

        while ((key = getch()) != 'q') 
        {
            if (!ondataIniziata) {
                if (ondata < numOndate) {
                    numZombie = ondate[ondata];
                    generaPosizioniZombie(posizioneZombie, numZombie);
                    memset(zombieColpito, 0, sizeof(zombieColpito));  // Resetta gli zombie colpiti
                    mostraInfoOndata(ondata + 1, numZombie);
                    ondataIniziata = 1;
                } else {
                    mostraVittoria();
                    break;
                }
            }

            switch(key) {
                case KEY_UP:
                case KEY_DOWN:
                case KEY_LEFT:
                case KEY_RIGHT:
                    muoviPlayer(&y, &x, key);
                    ondataIniziata = 2; // La ondata è ufficialmente iniziata dopo il primo movimento
                    break;
                case ' ':
                    sparo = 1;
                    ondataIniziata = 2; // La ondata è ufficialmente iniziata dopo il primo sparo
                    break;
            }

            if (sparo) 
            {
                aggiungiProiettile(&listaProiettili, creaProiettile(x, y, 0, -1));
                sparo = 0;
            }

            muoviProiettili(&listaProiettili, posizioneZombie, &numZombie, zombieColpito);
            disattivaProiettili(&listaProiettili, ALTEZZA, LARGHEZZA);

            if (numZombie == 0) {
                ondata++;
                ondataIniziata = 0;
                continue;
            }

            if (ondataIniziata == 2) { // Solo quando la ondata è ufficialmente iniziata
                if (contatoreMovimento % frequenzaMovimento == 0) 
                {
                    muoviZombie(posizioneZombie, numZombie, (Posizione){30, 50});
                    for (int i = 0; i < numZombie; ++i) {
                        if (zombieColpito[i] == 0 && posizioneZombie[i].a == 30 && posizioneZombie[i].b == 50) {
                            HPcasa -= 10;
                            posizioneZombie[i].a = -1;
                            posizioneZombie[i].b = -1;

                            // Rimuovi lo zombie raggiunto
                            for (int j = i; j < numZombie - 1; ++j) {
                                posizioneZombie[j] = posizioneZombie[j + 1];
                                zombieColpito[j] = zombieColpito[j + 1];
                            }
                            numZombie--;
                        }
                    }
                }

                erase();
                confini();
                disegnaOstacoli();
                disegnaCasa(20, 20);
                disegnaCasaPlayer(30, 50);
                disegnaCasa(10, 80);
                disegnaPlayer(y, x);
                disegnaProiettili(listaProiettili);
                disegnaZombie(posizioneZombie, numZombie, zombieColpito);
                mvprintw(1, 1, "HP Casa: %d", HPcasa);
                mvprintw(1, LARGHEZZA - 20, "Zombie Rimasti: %d", numZombie);
                refresh();

                if (HPcasa <= 0) {
                    mvprintw(ALTEZZA / 2, LARGHEZZA / 2 - 5, "GAME OVER");
                    refresh();
                    usleep(2000000);
                    break;
                }

                contatoreMovimento++;
                usleep(10000);
            }
        }

        endwin();
        liberaListaProiettili(listaProiettili);

    return 0;
}
