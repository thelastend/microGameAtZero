//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "ui.h"
#include "keyboard.h"


/**
 * @brief Construct a new UI::UI object
 * 
 */
UI::UI()
{
    uint8_t index = 0;
    cursor.textureCursor = NULL;
    for(index = 0; index < MAX_BUTTONS;index++)
    {
        buttonList[index] = NULL;
    }

    for(index = 0; index < MAX_UI_IMAGES;index++)
    {
        imageList[index] = NULL;
    }

    for(index = 0; index < MAX_TEXTS;index++)
    {
        textList[index] = NULL;
    }

    for(index = 0; index < MAX_NUMBERS;index++)
    {
        numberList[index] = NULL;
    }

    for(index = 0; index < MAX_RECT;index++)
    {
        rectList[index] = NULL;
    }

    for(index = 0; index < MAX_CHECK;index++)
    {
        checkboxList[index] = NULL;
    }
    countButton = 0;
    countImage = 0;
    countNumber = 0;
    countText = 0;
    countRect = 0;
    countCheckbox = 0;
    keyBoardShow = false;
}


/**
 * @brief Destroy the UI::UI object
 * 
 */
UI::~UI()
{
    uint8_t index = 0;
    cursor.textureCursor = NULL;
    for(index = 0; index < MAX_BUTTONS;index++)
    {
        buttonList[index]->~BUTTON();
        buttonList[index] = NULL;
    }

    for(index = 0; index < MAX_UI_IMAGES;index++)
    {
        imageList[index]->~IMAGE();
        imageList[index] = NULL;
    }

    for(index = 0; index < MAX_TEXTS;index++)
    {
        textList[index]->~TEXT();
        textList[index] = NULL;
    }

    for(index = 0; index < MAX_NUMBERS;index++)
    {
        numberList[index]->~NUMBER();
        numberList[index] = NULL;
    }

    for(index = 0; index < MAX_CHECK;index++)
    {
        checkboxList[index]->~CHECKBOX();
        checkboxList[index] = NULL;
    }
    cursor.textureCursor = NULL;

}


/**
 * @brief This function adds a new button to the UI interface.
 * 
 * @param pButton pointer to the button to be add
 * @return position of the button in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pButton is NULL
 */
microGameAtZero_err UI::addButton(BUTTON *pButton)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;

    if(countButton < MAX_BUTTONS && pButton != NULL)
    {
        for(uint8_t index = 0; index < MAX_BUTTONS;index++)
        {
            if(buttonList[countButton] == NULL)
            {
                buttonList[countButton] = pButton;
                error = countButton;
                countButton++;
                break;
            }
        }
    }
    
    return error;
}


/**
 * @brief This function sets the hidden flag of the selected button.
 * 
 * @param numberButton index of the selected button object
 * @param hiden if ture the button is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenButton(uint8_t numberButton, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberButton < MAX_BUTTONS)
    {
        if(buttonList[numberButton] != NULL)
        {
            buttonList[numberButton]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function changes the text on the selected button.
 * 
 * @param numberButton index of the selected button object
 * @param pText new text 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err UI::modifyButtonText(uint8_t numberButton, char *pText)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((numberButton < MAX_BUTTONS) && (pText != NULL))
    {
        if(buttonList[numberButton] != NULL)
        {    
            buttonList[numberButton]->setText(pText);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;    
}


/**
 * @brief This function sets the highlight status of the selected button.
 * 
 * @param numberButton index of the selected button object
 * @param high if true the highlight is on otherwise not
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::setHighLightButton(uint8_t numberButton, bool high)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((numberButton < MAX_BUTTONS))
    {
        if(buttonList[numberButton] != NULL)
        {    
            buttonList[numberButton]->setHighLight(high);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;       
}


/**
 * @brief This function removes the selected button from the UI interface.
 * 
 * @param numberButton index of the selected button object
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::removeButton(uint8_t numberButton)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberButton < MAX_BUTTONS)
    {
        if(buttonList[numberButton] != NULL)
        {    
            buttonList[numberButton]->~BUTTON();
            buttonList[numberButton] = NULL;
            countButton--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;   
}



/**
 * @brief This function returns the button object on the selected position.
 * 
 * @param numberButton index of the selected button object
 * @return BUTTON* button object on the selected position or NULL
 */
BUTTON * UI::getButton(uint8_t numberButton)
{
    if(numberButton < MAX_BUTTONS)
    {
        return buttonList[numberButton];
    }
    return NULL;  
}


/**
 * @brief This function returns the number of buttons in the UI interface.
 * 
 * @return uint8_t number of buttons
 */
uint8_t UI::getButtonAmount()
{
    return countButton;
}


/**
 * @brief This function adds a new cursor to the UI interface.
 * 
 * @param settings cursor settings
 * @return MICRO_GAME_AT_ZERO_OK everything is ok 
 */
microGameAtZero_err UI::addCursor(cursor_ui settings)
{
    cursor = settings;
    return MICRO_GAME_AT_ZERO_OK;
}


/**
 * @brief This function moves the cursor to the passed position.
 * 
 * @param position new cursor position
 */
void UI::moveCursorTo(vector2 position)
{
    cursor.position = position;
}


 /**
  * @brief This function sets the hidden flag of the cursor.
  *   
  * @param hiden if ture the cursor is hidden otherwise it will be shown.
  */
void UI::setHiddenCursor(bool hidde)
{
    cursor.hidden = hidde;
}


/**
 * @brief This function returns the cursor settings.
 * 
 * @return cursor_ui cursor settings.
 */
cursor_ui UI::getCursor()
{
    return cursor;
}


/**
 * @brief This function adds a new image to the UI interface.
 * 
 * @param pNewImage pointer to the new image to be add
 * @return position of the image in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pNewImage is NULL
 */
microGameAtZero_err UI::addImage(IMAGE *pNewImage)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;

    if(countImage < MAX_UI_IMAGES)
    {
        for(uint8_t index = 0; index < MAX_UI_IMAGES;index++)
        {
            if(imageList[countImage] == NULL)
            {
                imageList[countImage] = pNewImage;
                error = countImage;
                countImage++;
                break;
            }
        }
    }
    
    return error;
}



/**
 * @brief This function sets the hidden flag of the selected image.
 * 
 * @param numberImgae index of the selected image object
 * @param hidden if true the image is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenImage(uint8_t numberImgae, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberImgae < MAX_BUTTONS)
    {
        if(imageList[numberImgae] != NULL)
        {
            imageList[numberImgae]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function sets a new texture to the selected image.
 * 
 * @param numbImage index of the selected image object
 * @param pTexture pointer to the new texture
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no more space or invalide parameter 
 */
microGameAtZero_err UI::modifyImage(uint8_t numbImage, uint8_t *pTexture)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((numbImage < MAX_BUTTONS) && (pTexture != NULL))
    {
        if(imageList[numbImage] != NULL)
        {    
            imageList[numbImage]->changeImage(pTexture);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function removes the selected image from the UI interface.
 * 
 * @param imageNumber index of the selected image object
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter 
 */
microGameAtZero_err UI::removeImage(uint8_t imageNumber)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(imageNumber < MAX_BUTTONS)
    {
        if(imageList[imageNumber] != NULL)
        {    
            imageList[imageNumber]->~IMAGE();
            imageList[imageNumber] = NULL;
            countImage--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error; 
}


/**
 * @brief This function returns the selected image object.
 * 
 * @param imageNumber index of the selected image object
 * @return IMAGE* image object or NULL
 */
IMAGE * UI::getImage(uint8_t imageNumber)
{
    if(imageNumber < MAX_BUTTONS)
    {
        return imageList[imageNumber];
    }
    return NULL;  
}


/**
 * @brief This function returns the number of images in the UI interface
 * 
 * @return uint8_t number of images
 */
uint8_t UI::getImageAmount()
{
    return countImage;
}



/**
 * @brief This function adds a new text object to the UI interface.
 * 
 * @param pNewText pointer to the new text object to be add
 * @return position of the text object in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pNewText is NULL
 */
microGameAtZero_err UI::addText(TEXT *pNewText)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;

    if(countText < MAX_TEXTS)
    {
        for(uint8_t index = 0; index < MAX_TEXTS;index++)
        {
            if(textList[countText] == NULL)
            {
                textList[countText] = pNewText;
                error = countText;
                countText++;
                break;
            }
        }
    }
    
    return error;
}


/**
 * @brief This function sets the hidden flag of the selected text object.
 * 
 * @param numberText index of the selected text object
 * @param hidden if ture the text object is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenText(uint8_t numberText, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberText < MAX_BUTTONS)
    {
        if(textList[numberText] != NULL)
        {
            textList[numberText]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function changes the text of the selected text object.
 * 
 * @param textNumber index of the selected text object
 * @param pText pointer to the new text to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter 
 */
microGameAtZero_err UI::modifyText(uint8_t textNumber, char *pText)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((textNumber < MAX_BUTTONS) && (pText != NULL))
    {
        if(textList[textNumber] != NULL)
        {    
            textList[textNumber]->changeText(pText);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function removes the selected text object from the UI interface.
 * 
 * @param textNumber index of the selected text object
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::removeText(uint8_t textNumber)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(textNumber < MAX_BUTTONS)
    {
        if(textList[textNumber] != NULL)
        {    
            textList[textNumber]->~TEXT();
            textList[textNumber] = NULL;
            countText--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function returns the selected text object.
 * 
 * @param textNumber index of the selected text object
 * @return TEXT* text object
 */
TEXT * UI::getText(uint8_t textNumber)
{
    if(textNumber < MAX_BUTTONS)
    {
        return textList[textNumber];
    }
    return NULL;  
}


/**
 * @brief This function returns the amount of the text object in the UI interface.
 * 
 * @return uint8_t amount of the text objects
 */
uint8_t UI::getTextAmount()
{
    return countText;
}
    


/**
 * @brief This function adds a new number object to the UI interface.
 * 
 * @param pNewNumber pointer to the new number object to be add 
 * @return position of the number object in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pNewNumber is NULL
 */
microGameAtZero_err UI::addNumber(NUMBER *pNewNumber)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;
    
    if(countNumber < MAX_NUMBERS)
    {
        for(uint8_t index = 0; index < MAX_NUMBERS;index++)
        {
            if(numberList[countNumber] == NULL)
            {
                numberList[countNumber] = pNewNumber;
                error = countNumber;
                countNumber++;
                break;
            }
        }
    }
    
    return error;
}



/**
 * @brief This function sets the hidden flag of the selected number object.
 * 
 * @param numberNumber index of the selected number object
 * @param hidden if ture the number object is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenNumber(uint8_t numberNumber, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberNumber < MAX_BUTTONS)
    {
        if(numberList[numberNumber] != NULL)
        {
            numberList[numberNumber]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function changes the registered number of the selected number object.
 * 
 * @param numberNumber index of the selected number object
 * @param number new number
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::modifyNumber(uint8_t numberNumber, uint32_t number)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberNumber < MAX_BUTTONS)
    {
        if(numberList[numberNumber] != NULL)
        {    
            numberList[numberNumber]->changeNumber(number);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function removes the selected number object from the UI interface.
 * 
 * @param numberNumber index of the selected number object
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::removeNumber(uint8_t numberNumber)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberNumber < MAX_NUMBERS)
    {
        if(numberList[numberNumber] != NULL)
        {    
            numberList[numberNumber]->~NUMBER();
            numberList[numberNumber] = NULL;
            countNumber--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function returns the selected number object.
 * 
 * @param numberNumber index of the selceted number object
 * @return NUMBER* number object or NULL
 */
NUMBER * UI::getNumber(uint8_t numberNumber)
{
    if(numberNumber < MAX_BUTTONS)
    {
        return numberList[numberNumber];
    }
    return NULL;  
}



/**
 * @brief This function returns the amount of number object in the UI interface.
 * 
 * @return uint8_t amount of number objects
 */
uint8_t UI::getNumberAmount()
{
    return countNumber;
}


/**
 * @brief This function adds a new rect object to the UI interface.
 * 
 * @param pNewRect pointer to the new rect object to be add
 * @return position of the rect object in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pNewRect is NULL
 */
microGameAtZero_err UI::addRect(RECT *pNewRect)
{
   microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;

    if(countRect < MAX_RECT)
    {
        for(uint8_t index = 0; index < MAX_RECT;index++)
        {
            if(rectList[countRect] == NULL)
            {
                rectList[countRect] = pNewRect;
                error = countRect;
                countRect++;
                break;
            }
        }
    }
    
    return error;
}



/**
 * @brief This function sets the hidden flag of the selected rect object.
 * 
 * @param numberRect index of the selected rect object
 * @param hidden if ture the rect object is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenRect(uint8_t numberRect, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberRect < MAX_RECT)
    {
        if(rectList[numberRect] != NULL)
        {
            rectList[numberRect]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function changes the fill level of the selected rect object.
 * 
 * @param numberRect index of the selected rect object
 * @param percent new fill level in percent 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::modifyFillArea(uint8_t numberRect, uint8_t percent)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberRect < MAX_RECT)
    {
        if(rectList[numberRect] != NULL)
        {    
            rectList[numberRect]->setFillSize(percent);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function changes the fill color of the selected rect object.
 * 
 * @param numberRect index of the selected rect object
 * @param color new fill color
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter  
 */
microGameAtZero_err UI::modifyFillColor(uint8_t numberRect, uint8_t color)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberRect < MAX_RECT)
    {
        if(rectList[numberRect] != NULL)
        {    
            rectList[numberRect]->setFillColor(color);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function changes the line color of the selected rect object.
 * 
 * @param numberRect index of the selected rect object
 * @param color new line color
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err UI::modifyLineColor(uint8_t numberRect, uint8_t color)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberRect < MAX_RECT)
    {
        if(rectList[numberRect] != NULL)
        {    
            rectList[numberRect]->setLineColor(color);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function removes the selected rect object from the UI interface.
 * 
 * @param numberRect index of the selected rect object
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter  
 */
microGameAtZero_err UI::removeRect(uint8_t numberRect)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberRect < MAX_RECT)
    {
        if(rectList[numberRect] != NULL)
        {    
            rectList[numberRect]->~RECT();
            rectList[numberRect] = NULL;
            countRect--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function returns the selected rect object.
 * 
 * @param numberRect index of the selceted rect object
 * @return RECT* rect object
 */
RECT *UI::getRect(uint8_t numberRect)
{
    if(numberRect < MAX_RECT)
    {
        return rectList[numberRect];
    }
    return NULL;  
}


/**
 * @brief This function returns the amount of the rect object in the UI interface.
 * 
 * @return uint8_t amount of rect objects
 */
uint8_t UI::getRectAmount()
{
    return countRect;
}


/**
 * @brief This function adds a new checkbox object to the UI interface.
 * 
 * @param pNewCheck pointer to the new checkbox object to be add
 * @return position of the checkbox object in the array (identification number).  
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more space or pNewCheck is NULL
 */
microGameAtZero_err UI::addCheckBox(CHECKBOX *pNewCheck)
{
   microGameAtZero_err error = MICRO_GAME_AT_ZERO_FULL_ERROR;

    if(countCheckbox < MAX_CHECK)
    {
        for(uint8_t index = 0; index < MAX_CHECK;index++)
        {
            if(checkboxList[countCheckbox] == NULL)
            {
                checkboxList[countCheckbox] = pNewCheck;
                error = countCheckbox;
                countCheckbox++;
                break;
            }
        }
    }
    
    return error;
}



/**
 * @brief This function sets the hidden flag of the selected checkbox object.
 * 
 * @param numberCheck index of the selected checkbox object
 * @param hiden if ture the checkbox object is hidden otherwise it will be shown.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setHiddenCheck(uint8_t numberCheck, bool hidden)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberCheck < MAX_CHECK)
    {
        if(checkboxList[numberCheck] != NULL)
        {
            checkboxList[numberCheck]->setHidden(hidden);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}


/**
 * @brief This function sets the checked status of the selected checkbox object.
 * 
 * @param numberCheck index of the selected checkbox object
 * @param check if true the checkbox is checked otherwise not
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::setCheck(uint8_t numberCheck, bool check)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberCheck < MAX_CHECK)
    {
        if(checkboxList[numberCheck] != NULL)
        {    
            checkboxList[numberCheck]->changeCheck(check);
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function removes the selected checkbox from the UI interface.
 * 
 * @param numberCheck incdex of the selected check box object
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalide parameter
 */
microGameAtZero_err UI::removeCheck(uint8_t numberCheck)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(numberCheck < MAX_CHECK)
    {
        if(checkboxList[numberCheck] != NULL)
        {    
            checkboxList[numberCheck]->~CHECKBOX();
            checkboxList[numberCheck] = NULL;
            numberCheck--;
            error = MICRO_GAME_AT_ZERO_OK;
        }
    }
    return error;
}



/**
 * @brief This function returns the selected checkbox object.
 * 
 * @param numberCheck index of the selected checkbox object.
 * @return CHECKBOX* checkbox object
 */
CHECKBOX *UI::getCheckBox(uint8_t numberCheck)
{
    if(numberCheck < MAX_CHECK)
    {
        return checkboxList[numberCheck];
    }
    return NULL;  
}



/**
 * @brief This function returns the amount of checkbox object in the UI interface.
 * 
 * @return uint8_t amount of checkbox objects
 */
uint8_t UI::getCheckBoxAmount()
{
    return countCheckbox;
}


/**
 * @brief This function returns the fade status of the keyboard.
 * 
 * @return true the keyboard is fade out
 * @return false the keyboard is fade in
 */
bool UI::getKeyBoardShow()
{
    return keyBoardShow;
}



/**
 * @brief This function fades out the keyboard with the passed title and input text.
 * 
 * @param pTitle pointer to the title text to be set
 * @param pInput pointer to the input text to be set
 * @param maxInput max amount of input chars
 */
void UI::keyBoardUp(char* pTitle,char* pInput, uint8_t maxInput)
{
    KEYBOARD *keyBoard = KEYBOARD::getInstance();
    if(pTitle != NULL)
    {
        if(strlen(pTitle) < MAX_TITLE_LENGTH)
        {
            keyBoard->setTitle(pTitle);
        }
    }
    if(pInput != NULL)
    {
        if(strlen(pInput) < MAX_KEYBOARD_INPUT)
        {
            keyBoard->setInputText(pInput);
        }
    }
    keyBoard->setMaxInput(maxInput);
    keyBoardShow = true;
}



/**
 * @brief This function returns the input text if the enter key is press.
 * 
 * @param pInputText pointer to the input text
 * @return true the enter key is press
 * @return false the enter key is not press
 */
bool UI::inputTextKeyBoard(char* pInputText)
{
    KEYBOARD *keyBoard = KEYBOARD::getInstance();
    inputKeyBoardText = keyBoard->getInputText();
    if(inputKeyBoardText[0] != '\0')
    {
        keyBoardShow = false;
        if(inputKeyBoardText[0] == '\n')
        {
            pInputText = NULL;
        }
        else
        {   
            strcpy(pInputText,inputKeyBoardText);
        }
        return true;
    }

    return false; 
}