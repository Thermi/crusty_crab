CC=gcc
CFLAGS=-std=c11 -Wall -ggdb -O0 -fbuiltin -W -Wstrict-prototypes -Wreturn-type -Wsequence-point -pedantic -Wextra 
CFLAGSOPT=-std=c11 -Wall -ggdb -O2 -fbuiltin -W -Wstrict-prototypes -Wreturn-type -Wsequence-point -pedantic -Wextra 
DEBUGALL=-DDEBUG_ROT -DDEBUG_LFSR -DDEBUG_EAC -DDEBUG
SRCCO=crappy_one/crappy_one.c
SRCDBG=debug/debug.c
SRCBT=backtrack/backtrack.c
TRGT=crusty_crab.c

crusty: 
	$(CC) $(CFLAGS) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -DDEBUG -DDEBUG_EAC -o crusty_crab

crusty_opt: 
	$(CC) $(CFLAGSOPT) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -DDEBUG -DDEBUG_EAC -o crusty_crab_o2

crusty_dbg: 
	$(CC) $(CFLAGS) $(DEBUGALL) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -o crusty_crab_dbg

clean:
	rm -f crusty_crab crusty_crab_dbg
