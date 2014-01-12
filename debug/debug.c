/*
 * Gruppe 8:
 * --------
 *
 * Andrey Nikolaev, Anna Ostrovskaya, Oliver Gebhard, Noel Kuntze
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

#include "debug.h"


/*
 * Bei einem Fehler der den weiteren Programmablauf zu stark beeintraechtigt
 * gegebene Meldung ausgeben und Programm beenden.
 *
 */
void fatal(char *message) {
    char error_message[100];

    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

/*
 * unsichere String Funktionen,
 * um uint8_t ohne Compiler-Meldungen benutzen zu koennen
 *
 */
int bad_strncmp(uint8_t *dest, uint8_t *src, unsigned int length) {
    int status = 0;
    unsigned int i = 0;

    for (i = 0; i < length; i++) {
        if (dest[i] != src[i]) {
            status = -1;
        }
    }

    return status;
}

void bad_strncpy(uint8_t *dest, uint8_t *src, unsigned int length) {
    unsigned int i = 0;

    for (i = 0; i < length; i++) {
        dest[i] = src[i];
    }
}

/*
 * Speicheralloziierung mit Fehlerueberpruefung
 * malloc + calloc
 */
void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(sizeof(ptr)*size);
    if (ptr == NULL) {
        fatal("in ec_malloc() on memory allocation");
    }
    return ptr;
}
void *ec_calloc(unsigned int size) {
    void *ptr;
    ptr = calloc(0, sizeof(ptr)*size);
    if (ptr == NULL) {
        fatal("in ec_calloc() on memory allocation");
    }
    return ptr;
}

/*
 * Gegebenen String in Hex darstellen
 *
 */
void hex_dump(uint8_t *data_buffer, const unsigned int length) {
    uint8_t byte;
    unsigned int i, j;
    for (i = 0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if (((i % 16) == 15) || (i == length - 1)) {
            for (j = 0; j < 15 - (i % 16); j++) {
                printf("  ");
            }
            printf("| ");

            for (j = (i - (i % 16)); j <= i; j++) {
                byte = data_buffer[j];
                if ((byte > 31) && (byte < 127)) {
                    printf("%c", byte);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
}

/*
 * Fuer gegebenes Byte die gesetzten Bits zeigen
 *
 */
void bin_dump(uint8_t byte) {
    int i;

    printf("%02x ", byte);
    for (i = 7; i >= 0; i--) {
        printf("%d", (byte>>i) & 1);
    }
    printf("\n");
}

/*
 * Filehandling mit Fehlerpruefung
 * further reading:
 * man 3 open
 * man 3 close
 * man 3 read
 * man 3 write
 *
 * Inhalt aus Datei in Buffer schreiben oder
 * vice versa
 *
 */
int ec_open(const char *filename, int mode) {
    int fd;
    fd = open(filename, mode);
    if (fd == -1) {
        fatal("in ec_open() on opening file");
    } 
    return fd;
}

void ec_read(const char *filename, uint8_t *buffer, unsigned int bufferlength) {
    int fd;
    ssize_t len;

    fd = ec_open(filename, O_RDONLY); 

    len = read(fd, buffer, bufferlength);

    if (len == -1) {
        fatal("in ec_read() on reading file");
    }
    close(fd);
}

void ec_write(const char *filename, uint8_t *buffer, unsigned int bufferlength) {
    int fd;
    ssize_t len;

    fd = ec_open(filename, O_WRONLY); 

    len = write(fd, buffer, bufferlength);

    if (len == -1) {
        fatal("in ec_write() on writing file");
    }
    close(fd);
}
