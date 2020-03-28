//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "menuSystem.h"
#include "../core/middleware.h"

static uint8_t onSound[] = {
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
};


static uint8_t offSound[] = {
0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff,
0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0,
0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 
0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 
0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 
0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 
0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff,
0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0xff, 

};

static char buttonText[4][12] = {"System Menu","Volume","Brightness","Battery"};
static char soundOnOffText[2][10] = {"Sound On","Sound Off"};
static char fpsShow[] = {"Show FPS:"};
static char version[] = {"Version: "};
static char minus[2] = {"-"};
static char plus[2] = {"+"};
MENUSYSTEM* MENUSYSTEM::instance;
AUDIOENGINE* MENUSYSTEM::audio;
uint16_t MENUSYSTEM::sizeW;
uint16_t MENUSYSTEM::sizeH;
vector2  MENUSYSTEM::cursorPos;
cursor_ui MENUSYSTEM::cursorSettings;
UI*      MENUSYSTEM::menuUi;
BUTTON*   MENUSYSTEM::volumMinusButton;  
BUTTON*   MENUSYSTEM::volumPLusButton;
RECT*     MENUSYSTEM::volumeBar;
RECT*     MENUSYSTEM::brightnessBar;
RECT*     MENUSYSTEM::batteryBar;
BUTTON*   MENUSYSTEM::brightnessMinusButton;  
BUTTON*   MENUSYSTEM::brightnessPLusButton;  
TEXT*     MENUSYSTEM::title;
TEXT*     MENUSYSTEM::volumeText;
NUMBER*   MENUSYSTEM::volumeValue;
TEXT*     MENUSYSTEM::brightnessText;
NUMBER*   MENUSYSTEM::brightnessValue;
TEXT*     MENUSYSTEM::batteryText;
TEXT*     MENUSYSTEM::versionText;
TEXT*     MENUSYSTEM::versionNumb;
NUMBER*   MENUSYSTEM::batteryLevel;
IMAGE*    MENUSYSTEM::muteOnOff;
BUTTON*   MENUSYSTEM::soundButton;
SCENE*    MENUSYSTEM::menuScene;
uint8_t   MENUSYSTEM::display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
bool MENUSYSTEM::joyCheck;  
int16_t MENUSYSTEM::xCurs;
int16_t MENUSYSTEM::yCurs;
bool MENUSYSTEM::A_BCheck;
bool MENUSYSTEM::soundOnOffCheck;
bool MENUSYSTEM::fpsChangeCheck; 
TEXT*  MENUSYSTEM::fpsText;
CHECKBOX* MENUSYSTEM::fpsCheck;


/**
 * @brief Construct a new MENUSYSTEM::MENUSYSTEM object
 * 
 */
MENUSYSTEM::MENUSYSTEM()
{

    menuUi = new UI();
    xCurs = 0;
    yCurs = 53;
    cursorPos.set(xCurs,yCurs);
    joyCheck = true;
    A_BCheck = true;
    soundOnOffCheck = true;
    fpsChangeCheck = false;

    audio = AUDIOENGINE::getInstance();
    vector2 titlePosition(110,10); 
    vector2 textPosition(140,38); 
    vector2 numberPosition(155,53); 
    vector2 buttonSize(16,16);
    vector2 barSize(240,16);
    vector2 volumenMinusPosition(10,50);
    vector2 volumenPlusPosition(294,50);
    vector2 brightnessMinusPosition(10,90);
    vector2 brightnessPlusPosition(294,90);
    vector2 volumBarPosition(40,50);
    vector2 brightnessBarPosition(40,90);
    vector2 batteryBarPosition(40,130);
    vector2 imagePos(152,170);
    vector2 imageSize(16,16);
    vector2 fpsPosition(148,210);
    vector2 soundButtonPosition(10,170);
    vector2 soundButtonSize(90,16);
    
    //volume
    button_ui settingButtonMinus;
    settingButtonMinus.position = volumenMinusPosition;
    settingButtonMinus.highLightColor = 255;
    settingButtonMinus.highLightWidth = 3;
    settingButtonMinus.size = buttonSize;
    settingButtonMinus.buttonColor = 200;
    settingButtonMinus.textColor = 255;
    settingButtonMinus.font = FONT_10;
    settingButtonMinus.Hidden = false;
    settingButtonMinus.pText = minus;

    volumMinusButton = new BUTTON(settingButtonMinus);
    menuUi->addButton(volumMinusButton);

    button_ui settingButtonPlus;
    settingButtonPlus.position = volumenPlusPosition;
    settingButtonPlus.highLightColor = 255;
    settingButtonPlus.highLightWidth = 3;
    settingButtonPlus.size = buttonSize;
    settingButtonPlus.buttonColor = 200;
    settingButtonPlus.textColor = 255;
    settingButtonPlus.font = FONT_10;
    settingButtonPlus.Hidden = false;
    settingButtonPlus.pText = plus;
    volumPLusButton = new BUTTON(settingButtonPlus);
    menuUi->addButton(volumPLusButton);

  
    //brigthness
    settingButtonMinus.position = brightnessMinusPosition;
    brightnessMinusButton = new BUTTON(settingButtonMinus);
    menuUi->addButton(brightnessMinusButton);

    settingButtonPlus.position = brightnessPlusPosition;
    brightnessPLusButton = new BUTTON(settingButtonPlus); 
    menuUi->addButton(brightnessPLusButton);

    

    button_ui settingSound;
    settingSound.position = soundButtonPosition;
    settingSound.size = soundButtonSize;
    settingSound.highLightColor = 255;
    settingSound.highLightWidth = 3;
    settingSound.buttonColor = 200;
    settingSound.textColor = 255;
    settingSound.font = FONT_10;
    settingSound.Hidden = false;
    settingSound.pText = soundOnOffText[0];
    soundButton = new BUTTON(settingSound); 
    menuUi->addButton(soundButton);


    //Title
    text_ui settingText;
    settingText.font = FONT_10;
    settingText.hidden = false;
    settingText.position = titlePosition;
    settingText.textColor = 0xf0;
    settingText.pText = buttonText[0];
    title = new TEXT(settingText);
    menuUi->addText(title);


    //Text
    settingText.position = textPosition;
    settingText.pText = buttonText[1];
    volumeText = new TEXT(settingText);
    menuUi->addText(volumeText); 

    textPosition.set(115,78);
    settingText.position = textPosition;
    settingText.pText = buttonText[2];
    brightnessText = new TEXT(settingText);
    menuUi->addText(brightnessText); 

    textPosition.set(131,118);
    settingText.position = textPosition;
    settingText.pText = buttonText[3];
    batteryText = new TEXT(settingText);
    menuUi->addText(batteryText); 


    textPosition.set(10,213);
    settingText.position = textPosition;
    settingText.pText = fpsShow;
    fpsText = new TEXT(settingText);
    menuUi->addText(fpsText); 


    textPosition.set(190,213);
    settingText.position = textPosition;
    settingText.pText = version;
    versionText = new TEXT(settingText);
    menuUi->addText(versionText); 


    textPosition.set(270,213);
    settingText.position = textPosition;
    settingText.pText = VERSION;
    versionNumb = new TEXT(settingText);
    menuUi->addText(versionNumb); 

    //cursor
    cursorSettings.position = cursorPos;
    cursorSettings.textCursor = '>';
    cursorSettings.transparentColor = 0x50;
    cursorSettings.hidden = false;
    menuUi->addCursor(cursorSettings);



    //bars
    rect_ui rectSettings;
    rectSettings.position = volumBarPosition;
    rectSettings.size = barSize;
    rectSettings.lineWidth = 1;
    rectSettings.colorLine = 0xff;
    rectSettings.colorFill = 0xbC;
    rectSettings.hidden = false;
    
    volumeBar = new RECT(rectSettings);

    rectSettings.position = brightnessBarPosition;
    brightnessBar = new RECT(rectSettings);

    rectSettings.position = batteryBarPosition;
    batteryBar = new RECT(rectSettings);

    rectSettings.position = batteryBarPosition;
    batteryBar = new RECT(rectSettings);

    menuUi->addRect(volumeBar);
    menuUi->addRect(brightnessBar);
    menuUi->addRect(batteryBar);
    
    volumeBar->setFillSize(50);
    brightnessBar->setFillSize(50);
    batteryBar->setFillSize(50);

    //Numbers
    number_ui settingNumb;
    settingNumb.number = 0;
    settingNumb.position = numberPosition;
    settingNumb.hidden = false;
    settingNumb.font = FONT_10;
    settingNumb.textColor = 0xf0;

    volumeValue = new NUMBER(settingNumb);
    menuUi->addNumber(volumeValue);

    numberPosition.set(155,93);
    settingNumb.position = numberPosition;
    brightnessValue = new NUMBER(settingNumb);
    menuUi->addNumber(brightnessValue);

    numberPosition.set(155,133);
    settingNumb.position = numberPosition;
    batteryLevel = new NUMBER(settingNumb);
    menuUi->addNumber(batteryLevel);


    //checkBox
    checkBox_ui settingCheck;
    settingCheck.hidden = false;
    settingCheck.check = false;
    settingCheck.position = fpsPosition;
    fpsCheck = new CHECKBOX(settingCheck);
    menuUi->addCheckBox(fpsCheck);

    //image
    image_ui settingImage;
    settingImage.hidden = false;
    settingImage.position = imagePos;
    settingImage.size = imageSize;
    settingImage.pSprite = onSound;

    muteOnOff = new IMAGE(settingImage);
    menuUi->addImage(muteOnOff);

    menuScene = new SCENE();
    menuScene->addUI(menuUi);

}


/**
 * @brief Destroy the MENUSYSTEM::MENUSYSTEM object
 * 
 */
MENUSYSTEM::~MENUSYSTEM()
{

}

/**
 * @brief This function returns the system menu scene.
 * 
 * @return system menu scene
 */
SCENE* MENUSYSTEM::getScene()
{
    return menuScene;
}


/**
 * @brief This function handles the system menu logic.
 * 
 * @return true  show the fps
 * @return false don't show the fps
 */
bool MENUSYSTEM::menuSystemLogic()
{
    uint8_t brightness = getDisplayLight();
    uint8_t volume = audio->getMainVolume();
    uint8_t battery = batteryValue();

    if(getInputJoyPad(DOWN) && joyCheck)
    {
        if(yCurs == CURSOR_Y_MIN+CURSOR_Y_UPDATE)
        {
            yCurs +=  CURSOR_Y_UPDATE*2;
            xCurs =  CURSOR_X_MIN;     
        }
        else if(yCurs < CURSOR_Y_MAX)
            yCurs += CURSOR_Y_UPDATE;
            
        joyCheck = false;
    }
    else if (getInputJoyPad(UP) && joyCheck)
    {
        if(yCurs == CURSOR_Y_MAX-CURSOR_Y_UPDATE)
            yCurs -= CURSOR_Y_UPDATE*2;
        else if(yCurs > CURSOR_Y_MIN)
            yCurs -= CURSOR_Y_UPDATE;
        joyCheck = false;
    }
    else if (getInputJoyPad(LEFT) && joyCheck)
    {

        if(xCurs == CURSOR_X_MAX)
            xCurs -= CURSOR_X_UPDATE;
        joyCheck = false;
    }
    else if (getInputJoyPad(RIGHT) && joyCheck)
    {
        if(xCurs == CURSOR_X_MIN && yCurs < CURSOR_Y_MIN+CURSOR_Y_UPDATE*2)
            xCurs += CURSOR_X_UPDATE;
        joyCheck = false;
    }
    else if(!joyCheck && !getInputJoyPad(UP) && !getInputJoyPad(DOWN) &&
            !getInputJoyPad(LEFT) && !getInputJoyPad(RIGHT))
    {
        joyCheck = true;
    }
    cursorPos.set(xCurs,yCurs);
    menuUi->moveCursorTo(cursorPos);

    if((getInputButton(A_BUTTON) || getInputButton(B_BUTTON)) && A_BCheck )
    {
        if((xCurs == CURSOR_X_MIN) && (yCurs == CURSOR_Y_MIN))
        {
            if(volume > VOLUME_STEP)
            {
                volume -= VOLUME_STEP;
            }
            else
            {
                volume = MIN_VOLUME;
            }
            volumMinusButton->setHighLight(true);
            audio->setMainVolume(volume);
        }
        else if((xCurs == CURSOR_X_MAX) && (yCurs == CURSOR_Y_MIN))
        {
            if(volume < MAX_VOLUME)
            {
                volume += VOLUME_STEP;
            }
            else
            {
                volume = MAX_VOLUME;
            }
            volumPLusButton->setHighLight(true);
            audio->setMainVolume(volume);
        }
        else if((xCurs == CURSOR_X_MIN) && (yCurs == (CURSOR_Y_MIN + CURSOR_Y_UPDATE)))
        {
            if(brightness > BRIGHTNESS_STEP+5)
            {
                brightness -= BRIGHTNESS_STEP;
            }            
            else
            {
                brightness = MIN_BRIGHTNESS;
            }
            brightnessMinusButton->setHighLight(true);
            setDisplayLight(brightness);
            
        }
        else if((xCurs == CURSOR_X_MAX) && (yCurs == (CURSOR_Y_MIN + CURSOR_Y_UPDATE)))
        {
            if(brightness < MAX_BRIGHTNESS)
            {
                brightness += BRIGHTNESS_STEP;
            }            
            else
            {
                brightness = MAX_BRIGHTNESS;
            }
            brightnessPLusButton->setHighLight(true);
            setDisplayLight(brightness);           
        }
        else if((xCurs == CURSOR_X_MIN) && (yCurs == (CURSOR_Y_MAX-CURSOR_Y_UPDATE)))
        {
            if(soundOnOffCheck)
            {
                soundOnOffCheck = false;
                soundButton->setText(soundOnOffText[1]);
                muteOnOff->changeImage(offSound);
                audio->setMute(true);
            }            
            else
            {
                soundOnOffCheck = true;
                soundButton->setText(soundOnOffText[0]);
                muteOnOff->changeImage(onSound);
                audio->setMute(false);
            }
            soundButton->setHighLight(true);
                     
        }
        else if((xCurs == CURSOR_X_MIN) && (yCurs == (CURSOR_Y_MAX)))
        {
            if(!fpsChangeCheck)
            {
                fpsChangeCheck = true;
                fpsCheck->changeCheck(true);
            }            
            else
            {
                fpsChangeCheck = false;
                fpsCheck->changeCheck(false);
            }
        }
        A_BCheck = false;
    }
    else if(!getInputButton(A_BUTTON) && !getInputButton(B_BUTTON) && !A_BCheck )
    {
        A_BCheck = true;
        brightnessPLusButton->setHighLight(false);
        brightnessMinusButton->setHighLight(false);
        volumPLusButton->setHighLight(false);
        volumMinusButton->setHighLight(false);
        soundButton->setHighLight(false);
    }

    volumeBar->setFillSize(volume);
    volumeValue->changeNumber(volume);
    brightnessBar->setFillSize(brightness);
    brightnessValue->changeNumber(brightness);
    batteryBar->setFillSize(battery);
    batteryLevel->changeNumber(battery);

    return fpsChangeCheck;
 
}


