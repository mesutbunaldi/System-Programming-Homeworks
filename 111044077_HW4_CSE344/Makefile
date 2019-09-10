CC = gcc
DB = gdb
CFLAGS = -o
DFLAGS = -g
PROGNAME = 111044077_main

all:
	$(CC) -std=c11 -lpthread -lrt -c $(PROGNAME).c
	$(CC) $(PROGNAME).o -lpthread -lrt $(CFLAGS) $(PROGNAME)

debug:
	$(CC) $(DFLAGS) -lpthread -lrt $(PROGNAME).c $(CFLAGS) $(PROGNAME)
	$(DB) ./$(PROGNAME)

clean:
	rm -f $(PROGNAME) *.o 
