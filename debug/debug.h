#ifndef _debug_h
#define _debug_h 1

void fatal(char *message);

void *ec_malloc(unsigned int size);

void *ec_calloc(unsigned int size);

void hex_dump(char *data_buffer, const unsigned int length);

void bin_dump(char data_buffer);

int ec_open(const char *filename, int mode);

void ec_read(const char *filename, char *buffer, unsigned int bufferlength);

void ec_write(const char *filename, char *buffer, unsigned int bufferlength);

#endif