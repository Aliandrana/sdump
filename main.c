#include <stdio.h>
#include <stdlib.h>
#include "sdump.h"


int main(int argc, char **argv) {

    struct srom rom;
    struct srom_header hrom;

    rom = openRom(argv[1]);

    if(rom.fd < 0) {
        printf("Nao foi possivel abrir o arquivo\n");
    }

    if(isHeadered(&rom) == 1)
        printf("Possui header\n");
    else if(isHeadered(&rom) == 0)
        printf("Não possui header\n");
    else
        printf("ROM comrrompida\n");


    readHeader(&rom, &hrom);
    hrom.romName[20] = '\0';
    printf("%s\n", hrom.romName);

    return 0;

}
