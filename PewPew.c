#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define PROIETTILE_CHAR '-'
#define VELOCITA_PROIETTILE 1
#define HEIGHT 35
#define WIDTH 100

// Struttura per il giocatore
typedef struct Giocatore {
    int x;
    int y;
    char icon;
} Giocatore;

// Struttura per il proiettile
typedef struct Proiettile {
    int x;
    int y;
    int dx;
    int dy;
    int attivo;
    struct Proiettile *next;
} Proiettile;

// Funzione per creare un nuovo giocatore
Giocatore* creaGiocatore(int x, int y, char icon) {
    Giocatore *g = malloc(sizeof(Giocatore));
    g->x = x;
    g->y = y;
    g->icon = icon;
    return g;
}

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
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;
        }
        tmp = tmp->next;
    }
}

// Funzione per disegnare i proiettili
void disegnaProiettili(Proiettile *lista) {
    Proiettile *tmp = lista;
    while (tmp != NULL) {
        if (tmp->attivo) {
            mvprintw(tmp->y, tmp->x, "%c", PROIETTILE_CHAR);
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

void drawBorders() {
    int i;

    // Draw top and bottom borders
    for (i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "=");
        mvprintw(HEIGHT - 1, i, "=");
    }

    // Draw left and right borders
    for (i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "[");
        mvprintw(i, WIDTH - 1, "]");
    }
}

void drawObstacles() {
    // Draw some obstacles
    mvprintw(10, 40, "/////////");
    mvprintw(11, 40, "/////////");
    mvprintw(12, 40, "/////////");
    mvprintw(13, 40, "/////////");

    mvprintw(25, 90, "/////////");
    mvprintw(26, 90, "/////////");
    mvprintw(27, 90, "/////////");
    mvprintw(28, 90, "/////////");

    mvprintw(17, 60, "/////////");
    mvprintw(18, 60, "/////////");
    mvprintw(19, 60, "/////////");
    mvprintw(20, 60, "/////////");

    mvprintw(3, 10, "///////////////");

    mvprintw(6, 10, "///");
    mvprintw(7, 10, "///");
    mvprintw(8, 10, "///");
    mvprintw(9, 10, "///");
    mvprintw(10, 10, "///");
    mvprintw(11, 10, "///");

    mvprintw(15, 5, "/////////");
    mvprintw(16, 5, "      ///");
    mvprintw(17, 5, "      ///");
    mvprintw(18, 5, "      ///");
    mvprintw(19, 5, "/////////");
}

void drawHouse(int start_y, int start_x) {
    // Draw roof
    mvprintw(start_y - 1, start_x, "   /\\");
    mvprintw(start_y, start_x + 1, " /  \\ ");
    mvprintw(start_y + 1, start_x + 1, "/    \\");
    mvprintw(start_y - 1, start_x + 7, "    \\");
    mvprintw(start_y, start_x + 8, "    \\");
    mvprintw(start_y + 1, start_x + 8, "     \\");
    mvprintw(start_y - 2, start_x + 4, "_______");
    mvprintw(start_y + 1, start_x + 2, "____");
    mvprintw(start_y + 1, start_x + 7, "______");

    // Draw walls
    mvprintw(start_y + 2, start_x + 6, "|");
    mvprintw(start_y + 3, start_x + 6, "|");
    mvprintw(start_y + 2, start_x + 1, "|");
    mvprintw(start_y + 3, start_x + 1, "|");
    mvprintw(start_y + 2, start_x + 13, "|");
    mvprintw(start_y + 3, start_x + 13, "|");

    // Draw base
    mvprintw(start_y + 3, start_x + 2, "____");
    mvprintw(start_y + 3, start_x + 7, "______");

    // Draw toppings
    mvprintw(start_y + 2, start_x + 3, "[]");
    mvprintw(start_y + 2, start_x + 8, "[][]");
}

void drawPlayer(int y, int x, char icon) {
    // Draw player
    mvprintw(y, x, "|%c|", icon);
}

void movePlayer(Giocatore *g, int key) {
    // Move player based on key input
    switch (key) {
        case KEY_UP:
            if (g->y > 1) // Ensure the player doesn't move beyond top border
                g->y -= 1;
            break;
        case KEY_DOWN:
            if (g->y < HEIGHT - 2) // Ensure the player doesn't move beyond bottom border
                g->y += 1;
            break;
        case KEY_LEFT:
            if (g->x > 1) // Ensure the player doesn't move beyond left border
                g->x -= 1;
            break;
        case KEY_RIGHT:
            if (g->x < WIDTH - 4) // Ensure the player doesn't move beyond right border
                g->x += 1;
            break;
    }
}

int main() {
    initscr(); // Initialize ncurses
    curs_set(0); // Hide the cursor
    noecho(); // Don't echo user input
    keypad(stdscr, TRUE); // Enable arrow keys

    // Draw borders and obstacles
    drawBorders();
    drawObstacles();
    drawHouse(20, 20);
    drawHouse(30, 50);
    drawHouse(10, 80);

    // Draw the first player at the bottom of the screen
    Giocatore *giocatore1 = creaGiocatore(WIDTH / 2, HEIGHT - 2, '0');
    drawPlayer(giocatore1->y, giocatore1->x, giocatore1->icon);

    // Draw the second player at the top of the screen
    Giocatore *giocatore2 = creaGiocatore(WIDTH / 2, 1, 'X');
    drawPlayer(giocatore2->y, giocatore2->x, giocatore2->icon);

    // Lista dei proiettili
    Proiettile *listaProiettili = NULL;

    // Main loop to handle player movement and shooting
    int key;
    int player2_input = ERR; // Store input for player 2
    while ((key = getch()) != 'q') {
        movePlayer(giocatore1, key);

        // Update player 2 input if available
        if (player2_input == ERR) {
            player2_input = getch();
        }
        movePlayer(giocatore2, player2_input);
        player2_input = ERR; // Reset player 2 input

        erase(); // Clear the screen
        drawBorders();
        drawObstacles();
        drawHouse(20, 20);
        drawHouse(30, 50);
        drawHouse(10, 80);
        drawPlayer(giocatore1->y, giocatore1->x, giocatore1->icon);
        drawPlayer(giocatore2->y, giocatore2->x, giocatore2->icon);

        // Shoot from the first player when space is pressed
        if (key == ' ') {
            aggiungiProiettile(&listaProiettili, creaProiettile(giocatore1->x, giocatore1->y, 0, -1));
        }

        // Draw and move bullets
        disegnaProiettili(listaProiettili);
        muoviProiettili(&listaProiettili);

        // Disable bullets that go out of the window
        disattivaProiettili(&listaProiettili, HEIGHT, WIDTH);

        refresh(); // Refresh the screen
    }

    // End ncurses mode
    endwin();

    // Free the allocated memory for the players
    free(giocatore1);
    free(giocatore2);

    // Free the allocated memory for the list of bullets
    liberaListaProiettili(listaProiettili);

    return 0;
}
