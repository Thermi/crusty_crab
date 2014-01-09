/*
 * Gruppe 8:
 * --------
 *
 * Andrey Nikolaev, Anna Ostrovskaya, Noel Kuntze, Oliver Gebhard
 *
 */

#define _XOPEN_SOURCE 9001
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "crappy_one/crappy_one.h"
#include "debug/debug.h"
#include "backtrack/backtrack.h"

/*
 * Hauptprogramm fuer Verschluesselung und anschliessender
 * Schluesselsuche via Backtracking
 *
 */

int main (int argc, char *argv[])
{
    int i           = 0;
    int status      = -1;

    char *key       = NULL;
    char *rec_key   = NULL;
    char *plain     = NULL;
    char *cipher    = NULL;

/*
 * Dateinamen zuweisen
 *
 */
    const char *keyfile     = KEYFILE;
    const char *rec_keyfile = RECKEYFILE;
    const char *plaintext   = PLAINTEXT;
    const char *ciphertext  = CIPHERTEXT;

/*
 * Speicher alloziieren und Strings abschliessen
 * Stringabschluss unnoetig, da nie als String verwendet wird
 * sondern nur als folge von chars
 */
    key     = ec_malloc(KEYLEN+1);
    rec_key = ec_calloc(KEYLEN+1);
    plain   = ec_malloc(BUFFERLEN+1);
    cipher  = ec_malloc(BUFFERLEN+1);

    key[KEYLEN]         = '\0';
    rec_key[KEYLEN]     = '\0';
    plain[BUFFERLEN]    = '\0';
    cipher[BUFFERLEN]   = '\0';

/*
 * Anhand der Anzahl uebergebener Argumente pruefen ob
 * Inhalte aus Datei geladen werden oder aus Argumenten kopiert
 * kurzes Usage falls zuviele Argumente uebergeben werden
 *
 */
/*
 * Kopiere Inhalt von Datei oder von uebergebenen Argumenten
 * Selbstgestriktes strncpy:
 * Laenge der Eingabe wird nicht geprueft
 * Es wird davon ausgegangen dass 16 + 10 Zeichen uebergeben werden
 *
 */
    if (argc == 3) {
        for (i = 0; i < BUFFERLEN; i++) {
            plain[i]   = argv[1][i];
        }
#ifdef DEBUG
        printf("plain: \n");
        hex_dump(plain, BUFFERLEN);
#endif
        for (i = 0; i < KEYLEN; i++) {
            key[i]     = argv[2][i];
        }
#ifdef DEBUG
        printf("key: \n");
        hex_dump(key, KEYLEN);
#endif
    } else if (argc == 1) {
        ec_read(keyfile, key, KEYLEN);
        ec_read(plaintext, plain, BUFFERLEN);
    } else {
        printf("Usage:\n");
        printf("%s [plaintext] [key]\n", argv[0]);
        printf("or with plaintext and keyfile as file in the same directory\n");
        printf("%s\n", argv[0]);
        exit(1);
    }

/*
 * Makros fuer bedingte Kompilierung
 * wichtige Debug Informationen "dumpen"
 * in Hex bzw binaer darstellen
 *
 */
#ifdef DEBUG
    printf("plain: \n");
    hex_dump(plain, BUFFERLEN);
    printf("key: \n");
    hex_dump(key, KEYLEN);
#endif

/*
 * Aufruf des Ver- und Entschluesselungs- 
 * Algorithmuses
 *
 */
    lfsr(plain, cipher, key);

#ifdef DEBUG
    printf("cipher: \n");
    hex_dump(cipher, BUFFERLEN);
#endif

/*
 * Ohne Programmaufrufparameter wird chiffre
 * fuer spaetere Verwendung in Datei gespeichert
 *
 */
    if (argc == 1) {
        ec_write(ciphertext, cipher, BUFFERLEN);
    }

/*
 * Eigentlicher known plaintext Angriff
 * Ergebnis wird in rec_key gespeichert und 
 * bei Erfolg ausgegeben. Bei Misserfolg auch zu Debug zwecken
 *
 * status == 0 bedeutet, dass der Schluessel gefunden wurde
 * alles ungleich 0 ist ein Fehler
 *
 */
    printf("Step one\n");

    printf("???\n");

    status = backtrack(plain, cipher, rec_key, 0);

/*
 * Ergebnis wird in jedem Fall ausgegeben und je nach dem
 * wie Programm aufgerufen wird auch in eine Datei gespeichert
 *
 */
    if (status == 0) {
        if (argc == 1) {
            ec_write(rec_keyfile, rec_key, KEYLEN);
        } else {
            hex_dump(rec_key, KEYLEN);
        }

        printf("original key: ");
        for (i = 0; i < KEYLEN; i++) {
            printf("%c", key[i]);
        }
        printf("\n");

        printf("recovered key: ");
        for (i = 0; i < KEYLEN; i++) {
            printf("%c", rec_key[i]);
        }
        printf("\n");
    } else {
        printf("Couldn't recover key.\n");
        printf("Status = %d\n", status);
        printf("What I found: ");
        for (i = 0; i < KEYLEN; i++) {
            printf("%c", rec_key[i]);
        }
        printf("\n");
    }

    printf("Profit\n");

/*
 * Aufraeumen, speicher wieder freigeben
 * wird nicht benoetigt, da Programmende
 *
 */
    free(key);
    free(plain);
    free(cipher);
    free(rec_key);

    return 0;
}
