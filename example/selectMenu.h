#ifndef _SELCET_MENU_
#define _SELCET_MENU_

#include "../microGameAtZero/microGameAtZero.h"

enum selectMenuButton {
    PONG_BUTTON = 0,
    PLATFORM = 1,
    SHOOT = 2,
    MAX_BUTTON
};

enum sceneList {
    SELECT_SCENE = 0,
    PONG_SCENE = 1,
    PLATFORM_SCENE = 2,
    SHOOT_SCENE = 3
};


class selectMenu : public SCENE 
{

    public:
    selectMenu();
    ~selectMenu();
    virtual void sceneLogic(uint32_t deltaT);

    private:
    MICROGAMEATZERO *game;
    BUTTON* menuButtonList[3];
    UI *uiMenu;
    uint8_t currentPosition;


};

#endif               
