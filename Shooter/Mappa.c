#include <stdlib.h>
#include <time.h>
#include <graphics.h>

#define Largehzza 800
#define Altezza 600
#define NumOstacoli 50
#define DimsnioneOstacolo 20

void DisegnaOstacoli() 
{
    int i;
    for (i = 0; i < NumOstacoli; i++) 
    {
        int x = rand() % (Larghezza - DimensioneOstacolo);
        int y = rand() % (Altezza - DimensioneOstacolo);
        setfillstyle(SOLID_FILL, WHITE);
        bar(x, y, x + DimensioneOstacolo, y + DimensioneOstacolo);
    }
}

int main() 
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    srand(time(NULL));

    rectangle(0, 0, WIDTH - 1, HEIGHT - 1);

    drawObstacles();

    delay(5000);

    closegraph();
    return 0;
}