#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "sdump.h"

struct srom openRom(char *name) {

    struct srom rom;
    struct stat st;

    rom.fd = open(name, O_RDONLY);
    rom.romName = name;
    
    fstat(rom.fd, &st);

    rom.romSize = st.st_size;

    return rom;

}

int isHeadered(struct srom *rom) {

    if((rom->romSize % 1024) == 0) return 0;
    if((rom->romSize % 1024) == 512) return 1;

    return -1;

}

void readHeader(struct srom *rom, struct srom_header *hrom) {

    if(isHeadered(rom) == 0)
        lseek(rom->fd, 32704, SEEK_SET);
    else
        lseek(rom->fd, 65984, SEEK_SET);

    read(rom->fd, hrom, sizeof(struct srom_header));

}
