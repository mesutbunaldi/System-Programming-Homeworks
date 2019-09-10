CC = gcc
DB = gdb
CFLAGS = -o
DFLAGS = -g
PROGNAME = 111044077_main

all:
	$(CC) -std=c11 -lm -c $(PROGNAME).c
	$(CC) $(PROGNAME).o -lm $(CFLAGS) $(PROGNAME)

debug:
	$(CC) $(DFLAGS) -lm $(PROGNAME).c $(CFLAGS) $(PROGNAME)
	$(DB) ./$(PROGNAME)

clean:
	rm -f $(PROGNAME) *.o 
