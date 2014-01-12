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

#include "backtrack.h"
#include "../crappy_one/crappy_one.h"
#include "../debug/debug.h"

/*
 * Backtracking Algorithmus zum finden des Schluessels
 *
 * Input: Klartext, Chiffretext (zum Errechnen von z)
 *        den aktuellen Schluessel (bei Aufruf leer)
 *        die aktuelle Position
 *
 * Output: der berechnete Schluessel
 *
 * Umsetzung: Klartext, Chiffre und Speicher fuer den Schluessel werden
 *            als Pointer uebergeben.
 *            In jeder Runde wird ein Schluesselbyte berechnet (Abschnitt erweitere TL)
 *            und die aktuelle Position (pos) um eins erhoeht.
 *            Nachdem die ersten vier Byte gesetzt sind (zum ersten Eintritt in check_current_solution() hat pos den Wert 4!
 *            im Schluessel sind die Bytes 0..3 gesetzt) kann das erste mal geprueft werden, 
 *            ob die Bytes fuer die Loesung in Frage kommen. (Pruefe TL)
 *            
 *            Wenn alle 10 Bytes gesetzt sind (KEYLEN) wird die bisherige Loesung
 *            als komplett angesehn und ueberprueft (encrypt_and_compare).
 *            Ist die Loesung falsch wird via status eine Nachricht an den Aufrufer zurueckgesendet.
 *            Wichtig: in dieser Konstellation kann beim ueberpruefen der kompletten Loesung nicht 
 *            davon ausgangen werden, dass diese richtig ist. Diese Variante hat aber den Vorteil,
 *            dass der Rekursionsbaum nur 10 Ebenen hat.
 *
 * status == 0 bedeutet, der selbst errechnete Schluessel generiert den gleichen Chiffretext wie der
 *             originale Schluessel.
 *
 */

int backtrack(uint8_t *plain, uint8_t *cipher, uint8_t *key, int pos) {
    int status = -1;
    int i = 0;
    uint8_t byte;

/*
 * Pruefe Teilloesung nach 4 gesetzten Schluesselbytes (pos hat den Wert 4)
 *
 */
    if ((pos > 3) && (pos <= KEYLEN)) {
        if (check_current_solution(plain, cipher, key, pos) != 0) {
            return status;
        }
    }

/*
 * Lösung komplett?
 *
 */
    if (pos == KEYLEN) {
        return encrypt_and_compare(plain, cipher, key);
    }

/*
 * Erweitere Teilloesung:
 * Fuer alle moeglichen Werte im aktuell freien Feld.
 * Statt an jeder Position alle Moeglichkeiten durchzugehen, wird
 * dies nur fuer die Schluesselbytes 0,1 und 2 gemacht
 * anhand dieser werden die restlichen errechnet.
 *
 */
    if (pos < 3) {
        for (i = 0; i < 0x100; i++) {
            expand_current_solution(key, (((uint8_t) i) MOD 0x100), pos);
            status = backtrack(plain, cipher, key, (pos + 1));

            if (status == 0) {
                i = 0x101;
            }
        }
    }
    if ((pos >= 3) && (pos < KEYLEN)) {
        byte = (plain[(pos - 3)] XOR cipher[(pos - 3)]) MOD 0x100;
        expand_current_solution(key, ((byte - key[(pos - 3)]) MOD 0x100), pos);
        status = backtrack(plain, cipher, key, (pos + 1));
    }
    return status;
}

/*
 * Erweitere aktuelle Loesung mit gegebenem Zeichen (byte)
 * an gegebener Position im Schluessel (pos)
 *
 */
void expand_current_solution(uint8_t *key, uint8_t byte, int pos) {
    key[pos] = byte;
}

/*
 * Pruefe ob aktuelle Besetzung des Schluessels tatsaechlich als
 * Loesung in Frage kommt:
 *
 * Wird erst aufgerufen wenn pos auf 4 steht, das heisst die Bytes 0 bis 3
 * gesetzt sind.
 * Vergleiche ob das XOR von Klartext und Chiffre (byte bzw. z) mit dem 
 * Schluessel ((a_i + a_i+3) MOD 256) generiert werden kann.
 *
 * Falls nicht soll dies dem Aufrufer (andere Backtrack-Instanz) mitgeteilt
 * werden.
 *
 */
int check_current_solution(uint8_t *plain, uint8_t *cipher, uint8_t *key, int pos) {
    int status = -1;
    uint8_t byte;
    uint8_t temp1;

    byte = (plain[(pos - 4)] XOR cipher[(pos - 4)]) MOD 0x100;

    temp1 = (key[(pos - 1)] + key[(pos - 4)]) MOD 0x100;
    if (temp1 == byte) {
        status = 0;
    }
    return status;
}

/*
 * Pruefe ob gefundene Loesung auch richtig ist:
 * Erstellt Speicher fuer den selbst errechneten Chiffretext (compare).
 * Verschluesselt (lfsr) Klartext mit dem aktuellen Schluessel und vergleicht
 * das Ergebnis via strncmp() (returncodes: 0 bei Gleichheit [man 3 strncmp])
 * falls Chiffre uebereinstimmt wird 0 an den Aufrufer zurueckgegeben
 * diese wird bis ins Hauptprogramm (main) durchgereicht, dort wird
 * der gefundene Schluessel ausgegeben.
 * 
 */
int encrypt_and_compare(uint8_t *plain, uint8_t *cipher, uint8_t *key) {
    uint8_t *compare = NULL;
    int status = -1;

    compare = ec_calloc(BUFFERLEN+1);
    compare[BUFFERLEN] = '\0';

    lfsr(plain, compare, key);

    status = bad_strncmp(compare, cipher, BUFFERLEN);

#ifdef DEBUG_EAC
    if (status == 0) {
        printf("original ciphertext: \n");
        hex_dump(cipher, BUFFERLEN);
        printf("self calculated ciphertext: \n");
        hex_dump(compare, BUFFERLEN);
    }
#endif
    free(compare);

    if (status != 0) {
        status = -1;
    }

    return status;
}
