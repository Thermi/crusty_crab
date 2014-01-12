CC=gcc
CFLAGS=-std=c11 -Wall -ggdb -O0 -fbuiltin -W -Wstrict-prototypes -Wreturn-type -Wsequence-point -pedantic -Wextra 
CFLAGSOPT=-std=c11 -Wall -ggdb -O2 -mtune=native -fbuiltin -W -Wstrict-prototypes -Wreturn-type -Wsequence-point -pedantic -Wextra 
DEBUGALL=-DDEBUG_ROT -DDEBUG_LFSR -DDEBUG_EAC -DDEBUG
SRCCO=crappy_one/crappy_one.c
SRCDBG=debug/debug.c
SRCBT=backtrack/backtrack.c
SRCBT_V2=backtrack/backtrack_v2.c
TRGT=crusty_crab.c
CHKTRGT=check_solution.c

crusty_v1: 
	$(CC) $(CFLAGS) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -o crusty_crab_v1

crusty_v2: 
	$(CC) $(CFLAGS) $(SRCCO) $(SRCDBG) $(SRCBT_V2) $(TRGT) -o crusty_crab_v2

crusty_v1_dbg: 
	$(CC) $(CFLAGS) $(DEBUGALL) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -o crusty_crab_v1_dbg

crusty_v2_dbg: 
	$(CC) $(CFLAGS) $(DEBUGALL) $(SRCCO) $(SRCDBG) $(SRCBT_V2) $(TRGT) -o crusty_crab_v2_dbg


crusty_v1_opt: 
	$(CC) $(CFLAGSOPT) $(SRCCO) $(SRCDBG) $(SRCBT) $(TRGT) -o crusty_crab_v1_opt

crusty_v2_opt: 
	$(CC) $(CFLAGSOPT) $(SRCCO) $(SRCDBG) $(SRCBT_V2) $(TRGT) -o crusty_crab_v2_opt

check_solution:
	$(CC) $(CFLAGS) $(SRCCO) $(SRCDBG) $(SRCBT) $(CHKTRGT) -o check_solution

clean:
	rm -f crusty_crab_v1 crusty_crab_v2_dbg crusty_crab_v2 crusty_crab_v2_dbg crusty_crab_v1_opt crusty_crab_v2_opt check_solution
