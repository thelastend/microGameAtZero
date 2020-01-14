#ifndef _SDODROID_MICROGAMEATZERO_
#define _SDODROID_MICROGAMEATZERO_

#include "esp_system.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "esp_vfs_fat.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "esp_err.h"
#include "dirent.h"
#include "../../microGameAtZeroError.h"


#define MISO				19
#define MOSI				23
#define CLK					18
#define CS					22


#define MAX_LENGTH_NAME     40
#define MAX_SAVE_SIZE       128
#define SD_FOLDER           "/sd/microGame"
#define MAX_FOLDER_NAME     70


microGameAtZero_err initSD();
void unmountSD();
microGameAtZero_err writeTo(char fileName[MAX_LENGTH_NAME],char *text);
char* readFrom(char fileName[MAX_LENGTH_NAME]);
microGameAtZero_err getFiles(char *fileName[MAX_LENGTH_NAME]);



#endif