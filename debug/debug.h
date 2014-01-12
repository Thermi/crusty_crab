#ifndef _debug_h
#define _debug_h 1

void fatal(char *message);

void *ec_malloc(unsigned int size);

void *ec_calloc(unsigned int size);

void hex_dump(uint8_t *data_buffer, const unsigned int length);

void bin_dump(uint8_t data_buffer);

int ec_open(const char *filename, int mode);

void ec_read(const char *filename, uint8_t *buffer, unsigned int bufferlength);

void ec_write(const char *filename, uint8_t *buffer, unsigned int bufferlength);

void bad_strncpy(uint8_t *dest, uint8_t *src, unsigned int length);

int bad_strncmp(uint8_t *dest, uint8_t *src, unsigned int length);

#endif
