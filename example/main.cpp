
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

#include "microGameAtZero/microGameAtZero.h"
#include "pong.h"
#include "platform.h"
#include "selectMenu.h"
#include "shooter.h"
#include "sounds.h"





void setup()
{ 
    MICROGAMEATZERO *game;
    AUDIOENGINE* audio;
    selectMenu* select;
    SHOOTER* ship = new SHOOTER();
    settingsEngine settings;
    settings.maxFps = 60;
    settings.screenX = 240;
    settings.screenY = 240;

    game = MICROGAMEATZERO::getInstance();
    game->initMicroGameAtZero(settings);
    
    select = new selectMenu();
    game->addNewScene(select);
    setupPong(); 
    setupPlatform();
    game->addNewScene(ship);
    game->loadScene(0);

    audio = AUDIOENGINE::getInstance();
    audio->setSampleRate(SAMPLE_22_KHZ);

    audio->setChannel(CHANNEL1,mainSound,50,sizeof(mainSound));


    audio->startPlaying(CHANNEL1,0,false);

    game->startGame();

}

void loop()
{

}


