CC = gcc
DB = gdb
CFLAGS = -o
DFLAGS = -g
PROGNAME = 111044077_main
PROGNAMELS= ls
PROGNAMECAT= cat
PROGNAMEWC= wc
PROGNAMEPWD= pwd
PROGNAMECD= cd

all:
	$(CC) -std=c11  -c $(PROGNAME).c -c  $(PROGNAMELS).c -c  $(PROGNAMECAT).c -c  $(PROGNAMEWC).c -c  $(PROGNAMEPWD).c -c  $(PROGNAMECD).c
	$(CC) $(PROGNAME).o   $(CFLAGS) $(PROGNAME)
	$(CC) $(PROGNAMELS).o   $(CFLAGS) $(PROGNAMELS)
	$(CC) $(PROGNAMECAT).o   $(CFLAGS) $(PROGNAMECAT)
	$(CC) $(PROGNAMEWC).o   $(CFLAGS) $(PROGNAMEWC)
		$(CC) $(PROGNAMEPWD).o   $(CFLAGS) $(PROGNAMEPWD)
		$(CC) $(PROGNAMECD).o   $(CFLAGS) $(PROGNAMECD)
debug:
	$(CC) $(DFLAGS)  $(PROGNAME).c  $(PROGNAMELS).c  $(PROGNAMECAT).c $(PROGNAMEWC).c $(PROGNAMEPWD).c $(PROGNAMECD).c $(CFLAGS) $(PROGNAME) $(PROGNAMELS) $(PROGNAMECAT) $(PROGNAMEWC) $(PROGNAMEPWD) $(PROGNAMECD)
	$(DB) ./$(PROGNAME)

clean:
	rm -f $(PROGNAME) *.o $(PROGNAMELS) $(PROGNAMECAT) $(PROGNAMEWC) $(PROGNAMEPWD) $(PROGNAMECD)*.exec