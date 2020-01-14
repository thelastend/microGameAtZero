#include "selectMenu.h"

char pongText[] = {"Pong"};
char platText[] = {"platform"};
char shootText[] = {"shoot"};

selectMenu::selectMenu()
{ 
    game = MICROGAMEATZERO::getInstance();
    uiMenu = new UI();
    vector2 buttonPos(80,100);
    vector2 buttonSize(80,16);


    button_ui settingButton;
    settingButton.buttonColor = 200;
    settingButton.textColor = 255;
    settingButton.font = FONT_10;
    settingButton.highLightColor = 0xff;
    settingButton.highLightOn = true;
    settingButton.highLightWidth = 2;
    settingButton.position = buttonPos;
    settingButton.size = buttonSize;
    settingButton.pText = pongText;

    menuButtonList[0] = new BUTTON(settingButton);
    uiMenu->addButton(menuButtonList[0]);

    buttonPos.y = 140;
    settingButton.position = buttonPos;
    settingButton.pText = platText;
    settingButton.highLightOn = false;
    menuButtonList[1] = new BUTTON(settingButton);
    uiMenu->addButton(menuButtonList[1]);

    buttonPos.y = 180;
    settingButton.position = buttonPos;
    settingButton.pText = shootText;
    settingButton.highLightOn = false;
    menuButtonList[2] = new BUTTON(settingButton);
    uiMenu->addButton(menuButtonList[2]);

    currentPosition = 0;
    this->addUI(uiMenu);
}

selectMenu::~selectMenu()
{

}

void selectMenu::sceneLogic(uint32_t deltaT)
{
    static bool pressed = false;
    for(uint8_t ii = 0; ii < MAX_BUTTON;ii++)
        menuButtonList[ii]->setHighLight(false);
    
    if(game->getJoyPad(UP) && !pressed)
    {
      if(currentPosition > 0)
      {
        currentPosition--;
      }
      pressed = true;
    }
    else if(game->getJoyPad(DOWN) && !pressed)
    {
      if(currentPosition < (MAX_BUTTON-1))
      {
        currentPosition++;
      }
      pressed = true;
    }
    else if(!game->getJoyPad(DOWN) && !game->getJoyPad(UP) && pressed)
    {
      pressed = false;
    }

    menuButtonList[currentPosition]->setHighLight(true);

    if(game->getButton(A_BUTTON) || game->getButton(B_BUTTON))
    {
      if(currentPosition == PONG_BUTTON)
      {
        game->loadScene(PONG_SCENE);
      }
      else if(currentPosition == PLATFORM)
      {
        game->loadScene(PLATFORM_SCENE);
      }
      else if(currentPosition == SHOOT)
      {
        game->loadScene(SHOOT_SCENE);
      }
    } 
}