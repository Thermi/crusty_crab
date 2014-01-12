#ifndef _crappy_one_h
#define _crappy_one_h 1

#define KEYFILE     "keyfile"
#define RECKEYFILE  "recoveredkeyfile"
#define PLAINTEXT   "plaintext"
#define CIPHERTEXT  "ciphertext"

#define BUFFERLEN   16
#define KEYLEN      10

#define LEFT    0x08
#define RIGHT   0x20

#define XOR     ^
#define MOD     %
#define DIV     /
#define OR      |

uint8_t rotate_right(uint8_t rotate);

void lfsr(uint8_t *plain, uint8_t *cipher, uint8_t *key);

#endif
