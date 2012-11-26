#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

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

    int hist = 0;
    int i;
    u_int8_t header[512];

    lseek(rom->fd, 0, SEEK_SET);
    read(rom->fd, header, 512);

    for(i=0;i<512;i++)
        if(header[i] == 0x00) hist++;

    if((rom->romSize % 1024) == 0 && hist < 200) return 0;
    if((rom->romSize % 1024) == 512 || hist > 450) return 1;

    return -1;

}

/*
 * Procura pelo cabecalho usando uma heuristica muito porca. Parece que funciona hehehehe
 *
*/
void readHeader(struct srom *rom, struct srom_header *hrom) {

    int hist = 0;
    int blank = 0;
    int i;


    if(isHeadered(rom) == 0){
        lseek(rom->fd, 32704, SEEK_SET);


        read(rom->fd, hrom, sizeof(struct srom_header));

        for(i=0;i<21;i++){
            if(isascii(hrom->romName[i])) hist++;
            if(hrom->romName[i] == 0x20 || hrom->romName[i] == 0x00) blank++;
        }
        
        //printf("hist: %d blank: %d\n", hist, blank);

        if(hist < 20 || blank >= 18) {
            lseek(rom->fd, 65472, SEEK_SET);
            read(rom->fd, hrom, sizeof(struct srom_header));
        }

    }
    else if(isHeadered(rom) == 1) {
        lseek(rom->fd, 65984, SEEK_SET);

        read(rom->fd, hrom, sizeof(struct srom_header));

        for(i=0;i<21;i++) {
            if(isascii(hrom->romName[i])) hist++;
            if(hrom->romName[i] == 0x20 || hrom->romName[i] == 0x00) blank++;
        }
        

        if(hist < 20 || blank > 18) {
            lseek(rom->fd, 33216, SEEK_SET);
            read(rom->fd, hrom, sizeof(struct srom_header));
        }
    }

    // Caso nao tenha encontrado o cabecalho insere -'s no campo de nome
    hist = 0;
    blank = 0;
    for(i=0;i<21;i++){
        if(isascii(hrom->romName[i])) hist++;
        if(hrom->romName[i] == 0x20) blank++;
    }
    if(hist < 20 || blank > 18) {
        for(i=0;i<20;i++){
            hrom->romName[i] = 0x2d;
        }
    }


}
