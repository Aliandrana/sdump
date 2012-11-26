#include <stdio.h>
#include <stdlib.h>
#include "sdump.h"


int main(int argc, char **argv) {

    struct srom rom;
    struct srom_header hrom;

    if(argc < 2) {
        printf("Informe o caminho para a ROM\n");
        return 1;
    }

    rom = openRom(argv[1]);

    if(rom.fd < 0) {
        printf("Nao foi possivel abrir o arquivo\n");
    }

    if(isHeadered(&rom) != -1) {
        readHeader(&rom, &hrom);
        hrom.romName[20] = '\0';
        printf("ROM Name: %s\n", hrom.romName);
    }

    return 0;

}
