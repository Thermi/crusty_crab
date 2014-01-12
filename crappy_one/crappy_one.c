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

#include "crappy_one.h"
#include "../debug/debug.h"

/*
 * Rotation um 5 Bit nach rechts:
 *
 * Beispiel: 'A' (0x41)
 *
 * 'A'                   0100 0001  (0x41)
 *
 * 5 Bit nach rechts:    .... .010  (0x02)
 * 3 Bit nach links:     0000 1...  (0x08)
 * Oder Verknuepfung:   -----------
 *                       0000 1010  (0x0a)
 *
 */

uint8_t rotate_right(uint8_t rotate) {
    return (rotate>>5) OR (rotate<<3);
}

/*
 * Linear Feedback Shift Register:
 * Mit jedem Takt (clock) wird ein Byte des inneren Zustands veraendert.
 * Anfangszustand ist der Schluessel selbst (key).
 *
 * Schluessel selbst wird nicht veraendert (wird in inner_state kopiert).
 * aus der Aufgabenstellung:
 *          inner_state entspricht a
 *          temp entspricht z (a_i + a_i+3) gespeichert
 *          das XOR von Klartext und z ergibt den Chiffretext
 *
 *          der neue Zustand (a'_i bzw. rot5(a_i+10 XOR a_i+5)) wird auch in temp
 *          zwischengespeichert
 *
 * Der ganze Vorgang wird 16 (BUFFERLEN) Runden wiederholt.
 *
 */

void lfsr(uint8_t *plain, uint8_t *cipher, uint8_t *key) {
    int clock = 0;
    uint8_t temp;
    uint8_t *inner_state = NULL;

    inner_state = ec_malloc(KEYLEN+1);
    bad_strncpy(inner_state, key, KEYLEN);
    inner_state[KEYLEN] = '\0';

#ifdef DEBUG_LFSR
    printf("inner_state:\n");
    hex_dump(inner_state, KEYLEN);
#endif

    for (clock = 0; clock < BUFFERLEN; clock++) {
        temp                               = (inner_state[(clock % KEYLEN)] + inner_state[(clock + 3) % KEYLEN]) MOD 0x100;
        cipher[clock]                      = (plain[clock] XOR temp) MOD 0x100;

        temp                               = (inner_state[(clock + 10) % KEYLEN] XOR inner_state[(clock + 5) % KEYLEN]) MOD 0x100;
        inner_state[(clock + 10) % KEYLEN] = rotate_right(temp);

#ifdef DEBUG_LFSR
        hex_dump(inner_state, KEYLEN);
        hex_dump(cipher, BUFFERLEN);
#endif
    }

    free(inner_state);
}
