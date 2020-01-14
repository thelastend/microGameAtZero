#include "sdDriverOdroidGo.h"
#include "uartDriverOdroidGo.h"

static void createPath(char *path, char *fileName);




void createPath(char *path, char *fileName)
{
    path[0] = '\0';
    strcat(path,SD_FOLDER);
    path[strlen(path)] = '/';
    path[strlen(path)] = '\0';
    strcat(path,fileName);
}

microGameAtZero_err initSD()
{
    int8_t initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
    sdmmc_host_t sd = SDSPI_HOST_DEFAULT();
    sdspi_slot_config_t config = SDSPI_SLOT_CONFIG_DEFAULT();
    sdmmc_card_t* mountCard;
    esp_vfs_fat_sdmmc_mount_config_t mountConfig;
    char path[MAX_FOLDER_NAME];

    memset(path,'\0',MAX_FOLDER_NAME);

    sd.slot = VSPI_HOST;
    sd.max_freq_khz = SDMMC_FREQ_DEFAULT;
    config.dma_channel = 2;
   

    config.gpio_miso = (gpio_num_t)MISO;
    config.gpio_mosi = (gpio_num_t)MOSI;
    config.gpio_sck  = (gpio_num_t)CLK;
    config.gpio_cs = (gpio_num_t)CS;

    mountConfig.format_if_mount_failed = false;
    mountConfig.max_files = 8;
    mountConfig.allocation_unit_size = 16 * 1024;


    char dirName[] = "microGame";
   

    initErr = esp_vfs_fat_sdmmc_mount("/sd", &sd, &config, &mountConfig, &mountCard);
    if(initErr == ESP_OK)
    {
        FILE* file = fopen(SD_FOLDER, "r");
        if(file == NULL)
        {

            f_mkdir(dirName); 

        }
        else
        {
             fclose(file);
        }
        
        
        initErr = MICRO_GAME_AT_ZERO_OK;
    }


    return initErr;
}

microGameAtZero_err writeTo(char fileName[MAX_LENGTH_NAME], char *text)
{
    int8_t writeErr = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    char path[MAX_FOLDER_NAME];
    memset(path,'\0',MAX_FOLDER_NAME);

    if(strlen(fileName)< MAX_LENGTH_NAME)
    {

        createPath(path,fileName);
        FILE* file = fopen(path, "w");        
        if( file != NULL )
        {   
            fprintf(file, text);
            fclose(file);    
            writeErr = MICRO_GAME_AT_ZERO_OK;
            fclose(file);
        }
        else
        {
            writeErr = MICRO_GAME_AT_ZERO_SEND_ERROR;
        }
    }

    return writeErr;
}


char* readFrom(char fileName[MAX_LENGTH_NAME])
{
    static char text[MAX_SAVE_SIZE];
    char path[MAX_FOLDER_NAME];
    memset(path,'\0',MAX_FOLDER_NAME);
    memset(text,0,MAX_SAVE_SIZE);

    if(strlen(fileName)< MAX_LENGTH_NAME)
    {
        createPath(path,fileName);
        FILE* file = fopen(path, "r");


        if (file != NULL) 
        {
            fgets(text, MAX_SAVE_SIZE, file);
            fclose(file);        
        }  
        else
        {
            memset(text,'\0',MAX_SAVE_SIZE);
        }
             
    }
    return text;
}



microGameAtZero_err getFiles(char *fileName[MAX_LENGTH_NAME])
{
    int8_t getErr = MICRO_GAME_AT_ZERO_DIR_ERROR;
    int8_t fileCount = 0;

    DIR *dir = opendir(SD_FOLDER);
    if( dir != NULL )
    {

        struct dirent *file;
        while((file=readdir(dir)) != NULL)
        {
            size_t len = strlen(file->d_name);
            if(len >= MAX_LENGTH_NAME)
            {
                len = MAX_LENGTH_NAME;
            }
            if(file->d_name[0] != '.')//no hidden files
            {
                memcpy(fileName[fileCount],file->d_name,len);
                fileCount++;
            }
        }
        getErr = MICRO_GAME_AT_ZERO_OK;
        getErr = fileCount;

        closedir(dir);
    }

    return getErr;
}


void unmountSD()
{
    esp_vfs_fat_sdmmc_unmount();
}


