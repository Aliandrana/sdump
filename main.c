#include <stdio.h>
#include <stdlib.h>
#include "sdump.h"
#include <math.h>


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
        if(!rom.ok) {
            printf("Problemas na leitura do arquivo\n");
            return 1;
        }

        u_int8_t mapmodeAA, mapmodeB;

        printf("ROM Name:\t%s\n", hrom.romName);

        printf("Map Mode:\t");
        mapmodeAA = hrom.romMapMode & 0x30;
        mapmodeB = hrom.romMapMode & 0x01;
        if(mapmodeAA) 
            printf("FastROM\n");
        else if(mapmodeB)
            printf("FastROM\n");
        else
            printf("Desconhecido (0x%hhx)\n", hrom.romMapMode);
 


        printf("ROM Type:\t");
        switch(hrom.romType) {
            case 0x00:
                printf("ROM Only\n");
                break;
            case 0x01:
                printf("ROM + RAM\n");
                break;
            case 0x02:
                printf("ROM + RAM + SRAM\n");
                break;
            case 0x03:
                printf("DSP + ROM + Enhancement Chip\n");
                break;
            case 0x04:
                printf("DSP + ROM + Enhancement Chip + RAM\n");
                break;
            case 0x05:
                printf("DSP + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0x06:
                printf("DSP + ROM + Enhancement Chip + SRAM\n");
                break;
            case 0x13:
                printf("SuperFX + ROM + Enhancement Chip\n");
                break;
            case 0x14:
                printf("SuperFX + ROM + Enhancement Chip + RAM\n");
                break;
            case 0x15:
                printf("SuperFX + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0x16:
                printf("SuperFX + ROM + Enhancement Chip + SRAM\n");
                break;
            case 0x23:
                printf("OBC1 + ROM + Enhancement Chip\n");
                break;
            case 0x24:
                printf("OBC1 + ROM + Enhancement Chip + RAM\n");
                break;
            case 0x25:
                printf("OBC1 + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0x26:
                printf("OBC1 + ROM + Enhancement Chip + SRAM\n");
                break;
            case 0x33:
                printf("SA-1 + ROM + Enhancement Chip\n");
                break;
            case 0x34:
                printf("SA-1 + ROM + Enhancement Chip + RAM\n");
                break;
            case 0x35:
                printf("SA-1 + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0x36:
                printf("SA-1 + ROM + Enhancement Chip + SRAM\n");
                break;
            case 0xE3:
                printf("Other + ROM + Enhancement Chip\n");
                break;
            case 0xE4:
                printf("Other + ROM + Enhancement Chip + RAM\n");
                break;
            case 0xE5:
                printf("Other + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0xE6:
                printf("Other + ROM + Enhancement Chip + SRAM\n");
                break;
            case 0xF3:
                printf("Custom Ship + ROM + Enhancement Chip\n");
                break;
            case 0xF4:
                printf("Custom Ship + ROM + Enhancement Chip + RAM\n");
                break;
            case 0xF5:
                printf("Custom Ship + ROM + Enhancement Chip + RAM + SRAM\n");
                break;
            case 0xF6:
                printf("Custom Ship + ROM + Enhancement Chip + SRAM\n");
                break;
            default:
                printf("Desconhecido\n");
                break;
        }

        printf("ROM Size:\t");
        switch(hrom.romSize) {
            case 0x09:
                printf("3~4MBit\n");
                break;
            case 0x0A:
                printf("5~8MBit\n");
                break;
            case 0x0B:
                printf("9~16Mbit\n");
                break;
            case 0x0C:
                printf("17~32MBit\n");
                break;
            case 0x0D:
                printf("33~64MBit\n");
                break;
            default:
                printf("Desconhecido\n");
                break;
        }


        printf("SRAM Size:\t%.0fKB\n", 2048 * pow(2, hrom.romSRAMSize));

        printf("Dest. Code:\t");

        switch(hrom.romDstCode) {
            case 0x00:
                printf("Japan (J)\n");
                break;
            case 0x01:
                printf("North America - USA and Canada (E)\n");
                break;
            case 0x02:
                printf("All of Europe (P)\n");
                break;
            case 0x03:
                printf("Scandinavia (W)\n");
                break;
            case 0x06:
                printf("Europe - French Only (F)\n");
                break;
            case 0x07:
                printf("Dutch (H)\n");
                break;
            case 0x08:
                printf("Spanish (S)\n");
                break;
            case 0x09:
                printf("German (D)\n");
                break;
            case 0x0A:
                printf("Italian (I)\n");
                break;
            case 0x0B:
                printf("Chinese (C)\n");
                break;
            case 0x0D:
                printf("Korean (K)\n");
                break;
            case 0x0E:
                printf("Common (A)\n");
                break;
            case 0x0F:
                printf("Canada (N)\n");
                break;
            case 0x10:
                printf("Brazil (B)\n");
                break;
            case 0x11:
                printf("Australia (U)\n");
                break;
            case 0x12:
                printf("Other Variation (X)\n");
                break;
            case 0x13:
                printf("Other Variation (Y)\n");
                break;
            case 0x14:
                printf("Other Variation (Z)\n");
                break;
            default:
                printf("Desconhecido\n");
        }

        printf("Fixed Value:\t0x%hhx\n", hrom.romFixed);
        printf("Compl. Chksum:\t0x%hx\n", hrom.romCompCheck);
        printf("Checksum:\t0x%hx\n", hrom.romChecksum);

    }
        return 0;
}
