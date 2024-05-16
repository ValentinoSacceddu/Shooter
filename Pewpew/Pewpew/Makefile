CC=gcc

CFLAGS=-Iinclude

TARGET=pewpew

$(TARGET): main.o menu.o mappa.o ostacoli.o player.o proiettili.o zombie.o
	$(CC) -o $(TARGET) main.o menu.o mappa.o ostacoli.o player.o proiettili.o zombie.o

 main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -lncurses

mappa.o: src/mappa.c include/mappa.h
	$(CC) $(CFLAGS) -c src/mappa.c -lncurses

menu.o: src/menu.c include/menu.h
	$(CC) $(CFLAGS) -c src/menu.c -lncurses

ostacoli.o: src/ostacoli.c include/ostacoli.h
	$(CC) $(CFLAGS) -c src/ostacoli.c -lncurses

player.o: src/player.c include/player.h
	$(CC) $(CFLAGS) -c src/player.c -lncurses

proiettili.o: src/proiettili.c include/proiettili.h
	$(CC) $(CFLAGS) -c src/proiettili.c -lncurses

zombie.o: src/zombie.c include/zombie.h
	$(CC) $(CFLAGS) -c src/zombie.c -lncurses

clean:
	rm -f *.o $(TARGET)