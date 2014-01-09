#ifndef _backtrack_h
#define _backtrack_h 1

int backtrack(char *plain, char *cipher, char *key, int pos);

int encrypt_and_compare(char *plain, char *cipher, char *key);

int check_current_solution(char *plain, char *cipher, char *key, int pos);

void expand_current_solution(char *key, char byte, int pos);

#endif
