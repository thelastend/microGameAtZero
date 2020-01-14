//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "keyboard.h"
#include "../core/middleware.h"

static char keysSmall[AMOUNT_KEYS][2] = {{"1"},{"2"},{"3"},{"4"},{"5"},{"6"},{"7"},{"8"},{"9"},{"0"},{"-"},{"="},
{"q"},{"w"},{"e"},{"r"},{"t"},{"y"},{"u"},{"i"},{"o"},{"p"},{"["},{"]"},{"\\"},
{"a"},{"s"},{"d"},{"f"},{"g"},{"h"},{"j"},{"k"},{"l"},{":"},{"z"},{"x"},{"c"},{"v"},{"b"},{"n"},{"m"},{","},{"."}
,{"/"},{"'"}};
static char keysBig[AMOUNT_KEYS][2] = {{"!"},{"@"},{"#"},{"$"},{"%"},{"^"},{"&"},{"*"},{"("},{")"},{"_"},{"+"},
{"Q"},{"W"},{"E"},{"R"},{"T"},{"Y"},{"U"},{"I"},{"O"},{"P"},{"{"},{"}"},{"|"},
{"A"},{"S"},{"D"},{"F"},{"G"},{"H"},{"J"},{"K"},{"L"},{";"},{"Z"},{"X"},{"C"},{"V"},{"B"},{"N"},{"M"},{"<"},{">"}
,{"?"},{"\""}};
static char enter[] = {"OK"};
static char del[] = {"<-"};
static char shift[] = {"shift"};
static char space[] = {"space"};
static char titleText[MAX_TITLE_LENGTH] = {"Title"};

KEYBOARD* KEYBOARD::instance;
UI*       KEYBOARD::keyBoardUi;
TEXT*     KEYBOARD::title;
TEXT*     KEYBOARD::inputText;
SCENE*    KEYBOARD::keyBoardScene;
BUTTON*   KEYBOARD::buttonList[50];
uint8_t   KEYBOARD::display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
char      KEYBOARD::inputArray[MAX_KEYBOARD_INPUT];
uint8_t   KEYBOARD::onKeyBoardPos;
bool      KEYBOARD::shiftCheck;
bool      KEYBOARD::toChangCheck;
char      KEYBOARD::saveInput[MAX_KEYBOARD_INPUT];
uint16_t  KEYBOARD::arrayPos;
bool      KEYBOARD::joyPadCheck;
vector2   KEYBOARD::cursorPosition;
uint8_t   KEYBOARD::maxInput;
uint8_t   KEYBOARD::cursorPosBlick;

/**
 * @brief Construct a new KEYBOARD::KEYBOARD object
 * 
 */
KEYBOARD::KEYBOARD()
{
    vector2 size(15,15);
    vector2 position(20,120);
    vector2 textPosition(10,0);
    keyBoardUi = new UI();
    keyBoardScene = new SCENE();
    
    button_ui bSetting;
    bSetting.font = FONT_10;
    bSetting.buttonColor = 255;
    bSetting.textColor = 0x00;
    bSetting.size = size;
    bSetting.highLightWidth = 4;
    bSetting.highLightColor = 150;

    memset(inputArray,'\0',MAX_KEYBOARD_INPUT);
    
    for(uint8_t ii = 0;ii < AMOUNT_KEYS; ii++)
    {
        bSetting.position = position;
        bSetting.pText = keysSmall[ii];
        buttonList[ii] = new BUTTON(bSetting);
        keyBoardUi->addButton(buttonList[ii]);
    
        position.x += 20;
        if( (ii ==  (KEY_ROW_LINE-1) )|| (ii ==  ((KEY_ROW_LINE*2)-1) )
            || (ii ==  ((KEY_ROW_LINE*3)-1))  || (ii ==  ((KEY_ROW_LINE*4)-1)))
        {
           position.y += 20;
           position.x = 20;
        }
    }    
    buttonList[0]->setHighLight(true);
    position.x = 20;
    position.y +=20;
    size.x = 60;
    bSetting.size = size;
    bSetting.position = position;
    bSetting.pText = shift;
    buttonList[SHIFT_NUM] = new BUTTON(bSetting);
    keyBoardUi->addButton(buttonList[SHIFT_NUM]);

    position.x = 113;
    size.x = 120;
    bSetting.size = size;
    bSetting.position = position;
    bSetting.pText = space;
    buttonList[SPACE_NUM] = new BUTTON(bSetting); 
    keyBoardUi->addButton(buttonList[SPACE_NUM]);    
    
    position.x = 260;
    position.y = 120;
    size.x = 36;
    bSetting.size = size;
    bSetting.position = position;
    bSetting.pText = del;
    buttonList[DEL_NUM] = new BUTTON(bSetting);
    keyBoardUi->addButton(buttonList[DEL_NUM]);

    position.y += 20;
    size.x = 36;
    size.y = 60;
    bSetting.size = size;
    bSetting.position = position;
    bSetting.pText = enter;
    buttonList[ENTER_NUM] = new BUTTON(bSetting);
    keyBoardUi->addButton(buttonList[ENTER_NUM]);


    text_ui titleSetting;
    titleSetting.position = textPosition;
    titleSetting.font = FONT_10;
    titleSetting.textColor = 0xFF;
    titleSetting.pText = titleText;
    title = new TEXT(titleSetting);
    keyBoardUi->addText(title);

    textPosition.y = 20;
    titleSetting.position = textPosition;
    titleSetting.pText = inputArray;
    inputText = new TEXT(titleSetting);
    keyBoardUi->addText(inputText);


    cursorPosition.set(10,20);
    cursor_ui cursorSettings;
    cursorSettings.fontColor = 0xFF;
    cursorSettings.textCursor = '_';
    cursorSettings.hidden = false;
    cursorSettings.position = cursorPosition;
    keyBoardUi->addCursor(cursorSettings);
    

    shiftCheck = false;
    toChangCheck = true;
    joyPadCheck = true;
    onKeyBoardPos = 0;
    arrayPos = 0;
    cursorPosBlick = 0;
    memset(inputArray,'\0',MAX_KEYBOARD_INPUT);
    memset(saveInput,'\0',MAX_KEYBOARD_INPUT);
    maxInput = MAX_KEYBOARD_INPUT;
    keyBoardScene->addUI(keyBoardUi);
}


/**
 * @brief Destroy the KEYBOARD::KEYBOARD object
 * 
 */
KEYBOARD::~KEYBOARD()
{

}


/**
 * @brief This function returns the keyboard scene.
 * 
 * @return SCENE* keyboard scene
 */
SCENE* KEYBOARD::getScene()
{
    return keyBoardScene;
}


/**
 * @brief This function handles the inputs of the joypad.
 * 
 */
void KEYBOARD::inputJoyPad()
{

    if(getInputJoyPad(UP) && joyPadCheck)
    {   
        if(onKeyBoardPos >= KEY_ROW_LINE && onKeyBoardPos !=ENTER_NUM 
          && onKeyBoardPos != DEL_NUM && onKeyBoardPos != SPACE_NUM
          && onKeyBoardPos != SHIFT_NUM)
        {
            onKeyBoardPos -= KEY_ROW_LINE;            
        }
        else if( onKeyBoardPos == ENTER_NUM)
        {
            onKeyBoardPos = DEL_NUM;
        }
        else if( onKeyBoardPos == SHIFT_NUM)
        {
            onKeyBoardPos = 36;
        }
        else if( onKeyBoardPos == SPACE_NUM)
        {
            onKeyBoardPos = 40;
        }
        joyPadCheck = false;
    }
    else if(getInputJoyPad(DOWN) && joyPadCheck)
    {
        if(onKeyBoardPos < 36 && onKeyBoardPos !=ENTER_NUM 
          && onKeyBoardPos != DEL_NUM && onKeyBoardPos != SPACE_NUM
          && onKeyBoardPos != SHIFT_NUM)
        {
            onKeyBoardPos += KEY_ROW_LINE;            
        }
        else if( onKeyBoardPos == DEL_NUM)
        {
            onKeyBoardPos = ENTER_NUM;
        }
        else if( onKeyBoardPos >= 36 && onKeyBoardPos < 40)
        {
            onKeyBoardPos = SHIFT_NUM;
        }
        else if( onKeyBoardPos >= 40 && onKeyBoardPos < AMOUNT_KEYS)
        {
            onKeyBoardPos = SPACE_NUM;
        }
        joyPadCheck = false;
    }
    else if(getInputJoyPad(LEFT) && joyPadCheck)
    {
        if(((onKeyBoardPos > 0 && onKeyBoardPos < KEY_ROW_LINE ) ||
            (onKeyBoardPos > KEY_ROW_LINE && onKeyBoardPos < (KEY_ROW_LINE*2))  ||
            (onKeyBoardPos > (KEY_ROW_LINE*2) && onKeyBoardPos < (KEY_ROW_LINE*3)) ||
            (onKeyBoardPos > (KEY_ROW_LINE*3) && onKeyBoardPos < AMOUNT_KEYS))
          && onKeyBoardPos !=ENTER_NUM   
          && onKeyBoardPos != DEL_NUM && onKeyBoardPos != SPACE_NUM
          && onKeyBoardPos != SHIFT_NUM)
        {
            onKeyBoardPos -= 1;            
        }
        else if( onKeyBoardPos == DEL_NUM)
        {
            onKeyBoardPos = 11;
        }
        else if( onKeyBoardPos == ENTER_NUM)
        {
            onKeyBoardPos = 23;
        }
        else if( onKeyBoardPos == SPACE_NUM)
        {
            onKeyBoardPos = SHIFT_NUM;
        }

        joyPadCheck = false;
    }
    else if(getInputJoyPad(RIGHT) && joyPadCheck)
    {
        if(((onKeyBoardPos < (KEY_ROW_LINE-1)) ||
            (onKeyBoardPos > (KEY_ROW_LINE-1) && onKeyBoardPos < ((KEY_ROW_LINE*2)-1))  ||
            (onKeyBoardPos > ((KEY_ROW_LINE*2)-1) && onKeyBoardPos < ((KEY_ROW_LINE*3)-1)) ||
            (onKeyBoardPos > ((KEY_ROW_LINE*3)-1) && onKeyBoardPos < (AMOUNT_KEYS-1)))
          && onKeyBoardPos !=ENTER_NUM   
          && onKeyBoardPos != DEL_NUM && onKeyBoardPos != SPACE_NUM
          && onKeyBoardPos != SHIFT_NUM)
        {
            onKeyBoardPos += 1;            
        }
        else if( onKeyBoardPos == (KEY_ROW_LINE-1))
        {
            onKeyBoardPos = DEL_NUM;
        }
        else if( onKeyBoardPos == ((KEY_ROW_LINE*2)-1 ) || onKeyBoardPos == ((KEY_ROW_LINE*3)-1 ) ||
                onKeyBoardPos == ((KEY_ROW_LINE*4)-1 ) || onKeyBoardPos == (AMOUNT_KEYS-1) ||
                onKeyBoardPos == SPACE_NUM)
        {
            onKeyBoardPos = ENTER_NUM;
        }
        else if( onKeyBoardPos == SHIFT_NUM)
        {
            onKeyBoardPos = SPACE_NUM;
        }
        joyPadCheck = false;
    }
    else if(!joyPadCheck && !getInputJoyPad(UP) && !getInputJoyPad(DOWN) &&
            !getInputJoyPad(LEFT) && !getInputJoyPad(RIGHT))
    {
        joyPadCheck = true;
    }

}



/**
 * @brief This function handles the logic of the keyboard.
 * 
 */
void KEYBOARD::keyBoardLogic()
{
    bool pressA = getInputButton(A_BUTTON);
    bool pressB = getInputButton(B_BUTTON);
    static uint8_t saveonKeyBoardPos =onKeyBoardPos;
    inputJoyPad();


    if(onKeyBoardPos < AMOUNT_KEYS)
    {
        if((pressB || pressA)  && toChangCheck)
        {
            if(arrayPos < maxInput) 
            {
                if(!shiftCheck)
                {
                    inputArray[arrayPos] = keysSmall[onKeyBoardPos][0];
                    cursorPosBlick += getCharWidth(FONT_10,keysSmall[onKeyBoardPos][0]);
                }
                else
                {
                    cursorPosBlick += getCharWidth(FONT_10,keysBig[onKeyBoardPos][0]);                
                    inputArray[arrayPos] = keysBig[onKeyBoardPos][0];               
                }    
                arrayPos++;
            }
            toChangCheck = false;
        }
        else if((!pressB && !pressA) && !toChangCheck)
        {
            toChangCheck = true;
        }
        buttonList[onKeyBoardPos]->setHighLight(true);
        if(saveonKeyBoardPos != onKeyBoardPos)
        {
            buttonList[saveonKeyBoardPos]->setHighLight(false);
            saveonKeyBoardPos = onKeyBoardPos;
        }           
    }
    else
    {
        buttonList[saveonKeyBoardPos]->setHighLight(false); 
    }   
    

    if(onKeyBoardPos == SHIFT_NUM)
    {
        if((pressA || pressB) && !shiftCheck && toChangCheck)
        {
            shiftCheck = true;
            toChangCheck = false;
            for(uint8_t ii = 0;ii < AMOUNT_KEYS;ii++)
            {
                buttonList[ii]->setText(keysBig[ii]);
            }
        }
        else if((pressB || pressA) && shiftCheck && toChangCheck)
        {
            shiftCheck = false;
            toChangCheck = false;
            for(uint8_t ii = 0;ii < AMOUNT_KEYS;ii++)
            {
                buttonList[ii]->setText(keysSmall[ii]);
            }
        }
        else if((!pressB && !pressA) && !toChangCheck)
        {
            toChangCheck = true;
        }
        buttonList[SHIFT_NUM]->setHighLight(true);
    }
    else
    {
        buttonList[SHIFT_NUM]->setHighLight(false);        
    }

    if(onKeyBoardPos == SPACE_NUM)
    {
        if((pressB || pressA)  && toChangCheck)
        {
            if(arrayPos < maxInput)
            {
                inputArray[arrayPos] = ' ';
                cursorPosBlick += getCharWidth(FONT_10,' ');
                arrayPos++;
            }
            toChangCheck = false;
        }
        else if((!pressB && !pressA) && !toChangCheck)
        {
            toChangCheck = true;
        }
        buttonList[SPACE_NUM]->setHighLight(true);
    }
    else
    {
        buttonList[SPACE_NUM]->setHighLight(false);
    }

    if(onKeyBoardPos == DEL_NUM)
    {
        if((pressB || pressA)  && toChangCheck)
        {
            if(arrayPos > 0)
            {
                arrayPos--;
                cursorPosBlick -= getCharWidth(FONT_10,inputArray[arrayPos]);
                inputArray[arrayPos] = '\0';
            }
            toChangCheck = false;
        }
        else if((!pressB && !pressA) && !toChangCheck)
        {
            toChangCheck = true;
        }
        buttonList[DEL_NUM]->setHighLight(true);
    }
    else
    {
        buttonList[DEL_NUM]->setHighLight(false);
    }


    if(onKeyBoardPos == ENTER_NUM)
    {
        if((pressB || pressA)  && toChangCheck)
        {
            if(inputArray[0] == '\0')
            {
                saveInput[0] = '\n';
            }
            else
                strcpy(saveInput,inputArray);
        }
        else if((!pressB && !pressA) && !toChangCheck)
        {
            toChangCheck = true;
        }
        buttonList[ENTER_NUM]->setHighLight(true);
    }
    else
    {
        buttonList[ENTER_NUM]->setHighLight(false);
    }
    
    cursorPosition.x = 10 + cursorPosBlick;
    keyBoardUi->moveCursorTo(cursorPosition);
}



/**
 * @brief This function sets the title of the keyboard.
 * 
 * @param pText pointer to the title text to be set
 */
void KEYBOARD::setTitle(char* pText)
{
    title->changeText(pText);
    memset(inputArray,'\0',MAX_KEYBOARD_INPUT);
    memset(saveInput,'\0',MAX_KEYBOARD_INPUT);
    buttonList[0]->setHighLight(true);
    onKeyBoardPos = 0;
    cursorPosition.x = 10;
    keyBoardUi->moveCursorTo(cursorPosition);
    arrayPos = 0;
    cursorPosBlick = 0;
    strcpy(titleText,pText);
}



/**
 * @brief This function sets the shown input text.
 * 
 * @param input pointer to the input text
 */
void KEYBOARD::setInputText(char * pInput)
{
    
    arrayPos = strlen(pInput);
    if(arrayPos < maxInput)
    {
        strcpy(inputArray,pInput);
        for(uint8_t ii = 0; ii < strlen(inputArray);ii++)
            cursorPosBlick += getCharWidth(FONT_10,inputArray[ii]);
        cursorPosition.x = 10 + cursorPosBlick;
        keyBoardUi->moveCursorTo(cursorPosition);
    }
    else
    {
        arrayPos = 0;
    }
}


/**
 * @brief This function returns the input text.
 * 
 * @return char* input text
 */
char* KEYBOARD::getInputText()
{
    return saveInput;
}


/**
 * @brief This function sets the visibility of the cursors.
 * 
 * @param show if true is the cursor visible otherwise not
 */
void KEYBOARD::showCursor(bool show)
{
    keyBoardUi->setHiddenCursor(show);
}


/**
 * @brief This function sets the max length of the input text.
 * 
 * @param max max length of the input
 */
void KEYBOARD::setMaxInput(uint8_t max)
{
   if(max >  MAX_KEYBOARD_INPUT)
       maxInput = MAX_KEYBOARD_INPUT;
   else
       maxInput = max;
    
}