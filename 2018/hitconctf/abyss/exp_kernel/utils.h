#ifndef _UTILS_H
#define _UTILS_H

#include <sys/types.h>

int _getline(int fd, char *buff, size_t size);
void _puts(const char *buff);
void writeHex(uint64_t val);


#define puts _puts
#define getline _getline

#endif
