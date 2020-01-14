#ifndef _UI_MICROGAMEATZERO_
#define _UI_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"
#include "text.h"
#include "number.h"
#include "image.h"
#include "button.h"
#include "rect.h"
#include "checkBox.h"


/**
 * @brief structure of the cursor setting
 * 
 */
struct cursor_ui {
    bool hidden = true;
    vector2 position;
    uint8_t *textureCursor = NULL;
    vector2 sizeTexture;
    int32_t transparentColor = -1;
    char textCursor = 0;
    uint8_t fontColor = 0xff;
};


/**
 * @brief UI class
 * 
 */
class UI {

public: 
    UI();
    ~UI();
    microGameAtZero_err addButton(BUTTON *pButton);
    microGameAtZero_err setHiddenButton(uint8_t numberButton, bool hidden);
    microGameAtZero_err modifyButtonText(uint8_t numberButton, char *pText);
    microGameAtZero_err removeButton(uint8_t numberButton);
    microGameAtZero_err setHighLightButton(uint8_t numberButton, bool high);
    BUTTON * getButton(uint8_t numberButton);
    uint8_t getButtonAmount();

    microGameAtZero_err addCursor(cursor_ui settings);
    void moveCursorTo(vector2 position);
    void setHiddenCursor(bool hidde);
    cursor_ui getCursor();
    
    microGameAtZero_err addImage(IMAGE *pImage);
    microGameAtZero_err setHiddenImage(uint8_t numberImgae, bool hidden);
    microGameAtZero_err modifyImage(uint8_t numbImage, uint8_t *pTexture);
    microGameAtZero_err removeImage(uint8_t imageNumber);
    IMAGE * getImage(uint8_t imageNumber);
    uint8_t getImageAmount();

    microGameAtZero_err addText(TEXT *pText);
    microGameAtZero_err setHiddenText(uint8_t numberText, bool hidden);
    microGameAtZero_err modifyText(uint8_t textNumber, char *pText);
    microGameAtZero_err removeText(uint8_t textNumber);
    TEXT * getText(uint8_t textNumber);
    uint8_t getTextAmount();

    microGameAtZero_err addNumber(NUMBER *pNumber);
    microGameAtZero_err setHiddenNumber(uint8_t numberNumber, bool hidden);
    microGameAtZero_err modifyNumber(uint8_t numberNumber, uint32_t number);
    microGameAtZero_err removeNumber(uint8_t numberNumber);
    NUMBER * getNumber(uint8_t numberNumber);
    uint8_t getNumberAmount();

    microGameAtZero_err addRect(RECT *pRect);
    microGameAtZero_err setHiddenRect(uint8_t numberRect, bool hidden);
    microGameAtZero_err modifyFillArea(uint8_t numberRect,uint8_t percent);
    microGameAtZero_err modifyFillColor(uint8_t numberRect,uint8_t color);
    microGameAtZero_err modifyLineColor(uint8_t numberRect,uint8_t color);
    microGameAtZero_err removeRect(uint8_t numberRect);
    RECT *getRect(uint8_t numberRect);
    uint8_t getRectAmount();


    microGameAtZero_err addCheckBox(CHECKBOX *pCheck);
    microGameAtZero_err setHiddenCheck(uint8_t numberCheck, bool hidden);
    microGameAtZero_err setCheck(uint8_t numberCheck, bool check);
    microGameAtZero_err removeCheck(uint8_t numberCheck);
    CHECKBOX *getCheckBox(uint8_t numberCheck);
    uint8_t getCheckBoxAmount();


    bool getKeyBoardShow();
    void keyBoardUp(char* pTitle, char* pInput, uint8_t maxInput);
    bool inputTextKeyBoard(char* pInputText);
    
private:
    BUTTON *buttonList[MAX_BUTTONS];
    uint8_t countButton;
    cursor_ui cursor;
    IMAGE *imageList[MAX_UI_IMAGES];
    uint8_t countImage;
    TEXT *textList[MAX_TEXTS];
    uint8_t countText;
    NUMBER *numberList[MAX_NUMBERS];
    uint8_t countNumber;
    RECT *rectList[MAX_RECT];
    uint8_t countRect;
    CHECKBOX *checkboxList[MAX_CHECK];
    uint8_t countCheckbox;
    bool keyBoardShow;
    char* inputKeyBoardText;
};


#endif