#ifndef SDUMP_H
#define SDUMP_H

#include <sys/types.h>

struct srom {
    char *romName;
    int romSize;
    int fd;
};

struct srom_header {

    char romName[21];
    u_int8_t romMapMode;
    u_int8_t romType;
    u_int8_t romSize;
    u_int8_t romSRAMSize;
    u_int8_t romDstCode;
    u_int8_t romFixed;
    u_int8_t romVersion;
    u_int16_t romCompCheck;
    u_int16_t romChecksum;

};

struct srom openRom(char *);
int isHeadered(struct srom *);
void readHeader(struct srom *, struct srom_header *);


#endif // SDUMP_H
