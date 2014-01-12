/*
 * Gruppe 8:
 * --------
 *
 * Andrey Nikolaev, Anna Ostrovskaya, Noel Kuntze, Oliver Gebhard
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "crappy_one/crappy_one.h"
#include "debug/debug.h"
#include "backtrack/backtrack.h"

#define printHelpMessage() \
        printf("Usage: \n"); \
        printf("%s cleartext ciphertext key\n", argv[0]); \
        printf("or %s {-h, --help}\n", argv[0]); \
        printf("The inputs have to be 16 characters long each!\n");
/*
* Dieses Programm kann genutzt werden, um eine gefundene Lösung
* zu verifizieren, falls crusty_crab mit -O1 oder -O2 kompiliert wurde.
*
* Benutzung:
* --help und -h für eine Hilfenachricht
* check_solution Klartext Ciphertext Key
*/

int main(int argc, char *argv[]) {
    char *plaintext, *ciphertext,*key;
    if(argc == 2 && (strcmp(argv[1],"-h") || strcmp(argv[1], "--help")))
    {
        printHelpMessage()
        return 0;
    }
    if(argc != 4)
    {
        printf("This program must be used with the apropriate options!\n");
        printHelpMessage()
        return 1;
    }
    plaintext = ec_calloc(BUFFERLEN);
    ciphertext = ec_calloc(BUFFERLEN);
    key = ec_calloc(KEYLEN);

    strncpy(plaintext, argv[1], BUFFERLEN);
    strncpy(ciphertext, argv[2], BUFFERLEN);
    strncpy(key, argv[3], KEYLEN);

    plaintext[BUFFERLEN] = '\0';
    ciphertext[BUFFERLEN] = '\0';
    key[KEYLEN] = '\0';

    if (encrypt_and_compare(plaintext, ciphertext, key) == 0) {
        printf("Solution is correcct.\n");
        return 0;
    } else {
        printf("Solution is wrong.\n");
        return 1;
    }
    return 1;

}
