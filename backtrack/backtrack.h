#ifndef _backtrack_h
#define _backtrack_h 1

int backtrack(uint8_t *plain, uint8_t *cipher, uint8_t *key, int pos);

int encrypt_and_compare(uint8_t *plain, uint8_t *cipher, uint8_t *key);

int check_current_solution(uint8_t *plain, uint8_t *cipher, uint8_t *key, int pos);

void expand_current_solution(uint8_t *key, uint8_t byte, int pos);

#endif
