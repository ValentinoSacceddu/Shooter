all: run

CC=gcc -lncurses

CFLAGS=-Iinclude

TARGET = pewpew

$(TARGET): main.o menu.o mappa.o ostacoli.o player.o proiettili.o zombie.o HPcasa.o
	$(CC) -o $(TARGET) main.o menu.o mappa.o ostacoli.o player.o proiettili.o zombie.o HPcasa.o

 main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c 

mappa.o: src/mappa.c include/mappa.h
	$(CC) $(CFLAGS) -c src/mappa.c 

menu.o: src/menu.c include/menu.h
	$(CC) $(CFLAGS) -c src/menu.c 

ostacoli.o: src/ostacoli.c include/ostacoli.h
	$(CC) $(CFLAGS) -c src/ostacoli.c 

player.o: src/player.c include/player.h
	$(CC) $(CFLAGS) -c src/player.c 

proiettili.o: src/proiettili.c include/proiettili.h
	$(CC) $(CFLAGS) -c src/proiettili.c 

zombie.o: src/zombie.c include/zombie.h
	$(CC) $(CFLAGS) -c src/zombie.c 

HPcasa.o: src/HPcasa.c include/HPcasa.h
	$(CC) $(CFLAGS) -c src/HPcasa.c 

run: pewpew
	./pewpew

clean:
	rm -f *.o $(TARGET)