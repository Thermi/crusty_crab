CC=gcc
CFLAGS=-std=c11 -Wall -ggdb -O0 -fbuiltin -W -Wstrict-prototypes -Wreturn-type -Wsequence-point -pedantic -Wextra 
DEBUGALL=-DDEBUG_ROT -DDEBUG_LFSR -DDEBUG_EAC -DDEBUG
SRCCO=crappy_one/crappy_one.c
SRCDBG=debug/debug.c
SRCBT=backtrack/backtrack.c
TRGT=crusty_crab.c

crusty: 
	$(CC) $(CFLAGS) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -DDEBUG -DDEBUG_EAC -o crusty_crab

crusty_dbg: 
	$(CC) $(CFLAGS) $(DEBUGALL) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -o crusty_crab_dbg

clean:
	rm -f crusty_crab crusty_crab_dbg
