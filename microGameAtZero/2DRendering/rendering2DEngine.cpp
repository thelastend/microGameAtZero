//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "rendering2DEngine.h"
#include "../core/middleware.h"
#include "../Audio/audioEngine.h"
#include "../Physic/physicEngine.h"
#include "../Timer/timerEngine.h"
#include "../UI/ui.h"
#include "../Camera2d/camera2d.h"

RENDERING2D* RENDERING2D::instance;
uint16_t RENDERING2D::xPixelSizeScreen;
uint16_t RENDERING2D::yPixelSizeScreen;
uint16_t RENDERING2D::xSave;
uint16_t RENDERING2D::ySave;
uint8_t RENDERING2D::display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
KEYBOARD* RENDERING2D::keyBoard;
SCENE* RENDERING2D::keyScene;
bool RENDERING2D::collisionWindowShow;


/**
 * @brief Construct a new RENDERING2D::RENDERING2D object
 * 
 * @param x The x size of the display
 * @param y The y size of the display
 */
RENDERING2D::RENDERING2D(uint16_t x, uint16_t y)
{
    uint16_t startx = 0;
    uint16_t starty = 0;
    uint16_t endX = MAX_WIDHT_DISPLAY;
    uint16_t endY = MAX_HEIGHT_DISPLAY;
    if(x <= MAX_WIDHT_DISPLAY && y <= MAX_HEIGHT_DISPLAY && 
       x >= MIN_WIDHT_DISPLAY && y >= MIN_HEIGHT_DISPLAY)
    {
        xPixelSizeScreen = x;
        yPixelSizeScreen = y;
        xSave = x;
        ySave = y;

        startx = (MAX_WIDHT_DISPLAY/2) - (x/2);
        endX = (MAX_WIDHT_DISPLAY/2) + (x/2);

        starty = (MAX_HEIGHT_DISPLAY/2) - (y/2);
        endY = (MAX_HEIGHT_DISPLAY/2) + (y/2);

    }
    else
    {
        xPixelSizeScreen = MAX_WIDHT_DISPLAY;
        yPixelSizeScreen = MAX_HEIGHT_DISPLAY;
        xSave = MAX_WIDHT_DISPLAY;
        ySave = MAX_HEIGHT_DISPLAY;    
    }
    
    collisionWindowShow = false; 
    setupDisplay(startx, starty, endX, endY,SPI_SPEED, 5);
    keyBoard = KEYBOARD::getInstance();
    keyScene = keyBoard->getScene();
}

/**
 * @brief Destroy the RENDERING2D::RENDERING2D object
 * 
 */
RENDERING2D::~RENDERING2D()
{

}


/**
 * @brief This function renders the given text with the desired font and color to 
 *        the selected position.
 * 
 * @param text      
 * @param length        The length of the text
 * @param font          specification which font should be used
 * @param color         color of the text
 * @param position      The position from which to start drawing the text
 */
void RENDERING2D::drawChars(char *text, uint16_t length, fontType font, uint8_t color, vector2 position)
{
    uint8_t heightFont = 0;
    uint32_t pixelFont;
    int8_t fontRow;
    uint8_t fontPixelx = 0;
    uint8_t countNewLine = 0;
    uint8_t width;
    vector2 startPos;
    vector2 endPos;
    uint16_t saveXPosition = position.x;
                    
    getFontSize(font,&heightFont);
    uint8_t shiftFont = heightFont-1;

    if(text != NULL )
    {
        for(uint16_t indexChar = 0; indexChar < length;indexChar++)
        {
            width = getCharWidth(font, text[indexChar]);

            if(indexChar == 0)
                startPos.x = position.x;
            else
                startPos.x = endPos.x;
                            
            endPos.x = startPos.x+width;
            startPos.y = position.y + (heightFont*countNewLine);
            endPos.y = startPos.y + heightFont;
            fontRow = 0;
            
            if(text[indexChar] != '\n')
            {
                for(uint16_t yIndex = startPos.y; yIndex < endPos.y;yIndex++)
                {
                    pixelFont = setPixelForChar(text[indexChar],
                                                font,fontRow);
                    fontRow++;
                    fontPixelx = 0;
                    for(uint16_t xIndex = startPos.x; xIndex < endPos.x;xIndex++)
                    {
                        if((1 & (pixelFont >> (shiftFont-fontPixelx))) && (xIndex < xPixelSizeScreen)
                            && (yIndex < yPixelSizeScreen))
                        {
                            display[xIndex + (xPixelSizeScreen*yIndex)] = color;         
                        }
                        
                        fontPixelx++;
                    }
                }
            }
            else
            {
                position.x = saveXPosition - (heightFont*(indexChar+1));  
                countNewLine++;
            }
        }    
    }
}


/**
 * @brief This function renders the passed scene or the system menu.     
 * 
 * @param loadedScene   the scene to be rendered
 * @param fps           current fps
 * @param showFPS       if true the fps will be rendered otherwise not
 * @param systemMenu    if true the system menu will be rendered in place of the scene otherwise the scene 
 * @param deltaT        The time that has passed since last time render
 */
void RENDERING2D::renderingScreen(SCENE* loadedScene, uint8_t fps, bool showFPS, bool systemMenu, uint32_t deltaT)
{
    uint16_t indexY = 0;
    uint16_t indexX = 0;
    uint16_t countTilePixelX =  0;
    uint16_t countTilePixelY =  0;
    uint16_t tileMapPosition = 0;
    uint16_t row = 0;
    uint8_t textNum = NO_TILE_USEDED;
    scroll_s scroll;
    char* inputText;
    UI *ui = NULL;
    vector2 camPosition;
    static bool screenSaveSize = false;
    static bool courserShow = true;
    static uint8_t countCourserShow = 0;
    uint8_t backColor;

    
    if(loadedScene != NULL)
    {
        tileMap mapOB;
        tileMap mapBack;
        uint16_t maxTiles;
        uint16_t limitPosition;
        bool cameraStatus = false;
        CAMERA2D *camera2D = loadedScene->getCamera();

        backColor = loadedScene->getBackgroundColor();

        ui = loadedScene->getUI();

        if(ui != NULL)
        {
            if(ui->getKeyBoardShow())
            {
                keyBoard->keyBoardLogic();
                inputText = keyBoard->getInputText();
                if(inputText[0] == '\0')
                {
                    loadedScene = keyScene;
                    ui = loadedScene->getUI();
                    systemMenu = true;
                }

                if(countCourserShow > (fps/2))
                {
                    countCourserShow = 0;
                    keyBoard->showCursor(courserShow);
                    courserShow  ^= true;
                }
                else
                {
                    countCourserShow++;
                }
                
            }
        }

        if(systemMenu && !screenSaveSize)
        {
            setWindowArea(0,0,MAX_WIDHT_DISPLAY,MAX_HEIGHT_DISPLAY,SET_AREA_SAVE);
            xPixelSizeScreen = MAX_WIDHT_DISPLAY;
            yPixelSizeScreen = MAX_HEIGHT_DISPLAY;
            screenSaveSize = true;
        }
        else if(screenSaveSize && !systemMenu)
        {
            xPixelSizeScreen = xSave;
            yPixelSizeScreen = ySave;
            fillRect(0, 0, MAX_WIDHT_DISPLAY, MAX_HEIGHT_DISPLAY, 0x125);
            setWindowArea(((MAX_WIDHT_DISPLAY/2) - (xSave/2)),((MAX_HEIGHT_DISPLAY/2) - (ySave/2)),
                        ((MAX_WIDHT_DISPLAY/2) + (xSave/2)),((MAX_HEIGHT_DISPLAY/2) + (ySave/2)),SET_AREA_SAVE);
            screenSaveSize = false;
        }

        if(camera2D != NULL )
        {
           cameraStatus = camera2D->getCameraStatus();

        }

        for(uint16_t ii = 0; ii < yPixelSizeScreen;ii++)
        {
            for(uint16_t ll = 0; ll < xPixelSizeScreen;ll++)
            {
                display[ll + (xPixelSizeScreen*ii)] = backColor;
            }
        }
        scroll.direction.set(0,0);
        if(cameraStatus)
        {
            scroll = camera2D->getScrollTile();
            camPosition = camera2D->getCameraPosition();
            countTilePixelY = scroll.direction.y;
            row = scroll.scrollRow;
        }


        mapBack = loadedScene->getTileMap(BACKGROUND_LAYER);
        mapOB = loadedScene->getTileMap(OBJECT_LAYER);

        maxTiles = mapBack.amountTile.x*mapBack.amountTile.y;
        limitPosition = maxTiles - mapBack.amountTile.x;
        int16_t checkPosition = limitPosition - mapBack.amountTile.x;
        vector2 tileSize = mapBack.tileSize;

        if((maxTiles == 0))
        {
            maxTiles = mapOB.amountTile.x*mapOB.amountTile.y;
            limitPosition = maxTiles - mapOB.amountTile.x;
            checkPosition = limitPosition - mapOB.amountTile.x;
            tileSize = mapOB.tileSize;
        }            

        uint8_t pixelBack = 0;
        uint8_t pixelObject = 0;
        int32_t transpColorBack = -1;
        int32_t transpColorObject = -1;
        textureTile * textureBack = NULL;
        textureTile * textureObject = NULL;

        if((mapBack.order != NULL) || (mapOB.order != NULL))
        {        
            for(indexY = 0; indexY < yPixelSizeScreen; indexY++)
            {
                countTilePixelX = scroll.direction.x;
                if(!(countTilePixelY < tileSize.y))
                {
                    countTilePixelY = 0;
                    row++;
                }

                tileMapPosition = scroll.scrollTile + mapOB.amountTile.x*row;

                if(tileMapPosition > checkPosition)
                {
                    if(!cameraStatus)
                        tileMapPosition = 0;
                }
                
                uint8_t objectLayerNum = NO_TILE_USEDED;

                
                for(indexX = 0; indexX < xPixelSizeScreen; indexX++)
                {
                    if(!(countTilePixelX < tileSize.x))
                    {
                        countTilePixelX = 0;
                        tileMapPosition++;
                    }
                    textNum = NO_TILE_USEDED;
                    objectLayerNum = NO_TILE_USEDED;
                    if(tileMapPosition < maxTiles)
                    {
                        if(mapBack.order != NULL)
                            textNum = mapBack.order[tileMapPosition];  
                        
                        if(mapOB.order != NULL)
                            objectLayerNum =  mapOB.order[tileMapPosition];


                        if(textNum != NO_TILE_USEDED)
                        {
                            textureBack = loadedScene->getTexture(textNum);
                            pixelBack = textureBack->texture[countTilePixelX + (tileSize.x*countTilePixelY)];
                            transpColorBack = textureBack->transparentColor;
                        }
                        
                        if(objectLayerNum != NO_TILE_USEDED)
                        {
                            textureObject = loadedScene->getTexture(objectLayerNum);
                            pixelObject = textureObject->texture[countTilePixelX + (tileSize.x*countTilePixelY)];
                            transpColorObject = textureObject->transparentColor;                            
                        }

                        if((transpColorObject != pixelObject) && (objectLayerNum != NO_TILE_USEDED))
                        {
                            display[indexX + (xPixelSizeScreen*indexY)] = pixelObject;
                        } 
                        else if ((transpColorBack != pixelBack) && (textNum != NO_TILE_USEDED))
                        {
                            display[indexX + (xPixelSizeScreen*indexY)] = pixelBack;
                        }                    
                    }

                    countTilePixelX++;
                }
                countTilePixelY++;
            }
        }

        uint8_t numberOfObjects[OBJECTS_TYPES];
        uint16_t objectIndex = 0;
        numberOfObjects[KINECT] = loadedScene->getKinectCount();
        numberOfObjects[RIGID] = loadedScene->getRigidCount();
        numberOfObjects[STATIC] = loadedScene->getStaticCount();
        bool hidden = false;

        for(uint8_t ii = 0; ii < OBJECTS_TYPES; ii++)
        {
            objectIndex = 0;
            uint8_t index = 0;
            while(objectIndex <numberOfObjects[ii])
            {
                Object * object;
                if(ii == KINECT)
                {
                    object = loadedScene->getKinect(index);
                }
                else if(ii == RIGID)
                {
                    object = loadedScene->getRigid(index);
                    if(object != NULL)
                        loadedScene->getRigid(index)->update(deltaT);
                }
                else
                {
                    object = loadedScene->getStatic(index);
                }
                index++;
                if(object != NULL)
                {
                    objectIndex++;
                    int32_t transparentColor = object->getTransparentColor();
                    uint8_t * texture = object->getTexture();
                    uint8_t pixel = 0;
                    objectSettings values = object->getValues();
                    hidden = object->getHidden();
                    collisionSettings colWindow = object->getCollisionWindow();
                    if(!hidden)
                    {
                        int32_t xPosition = 0;
                        int32_t yPosition = 0;
                        int32_t xCol = 0;
                        int32_t yCol = 0;
                        uint16_t x;
                        uint16_t y;
                                
                        xPosition = values.position.x - camPosition.x;
                        yPosition = values.position.y - camPosition.y;

                        xCol = colWindow.position.x - camPosition.x;
                        yCol = colWindow.position.y - camPosition.y;

                        if((xPosition <xPixelSizeScreen)&&(xPosition  >= 0) &&
                            (yPosition < yPixelSizeScreen)&&(yPosition >= 0)                   )
                        {

                            for(uint16_t height = 0; height < values.size.y; height++)
                            {
                                for(uint16_t width = 0; width < values.size.x; width++)
                                {
                                    pixel = texture[width +(values.size.x*height)];

                                    x = xPosition+width;
                                    y = yPosition+height;

                                    if((collisionWindowShow)&&(x >= xCol && x <(xCol+colWindow.size.x)) && (y >= yCol && y <(yCol+colWindow.size.y)))
                                    {
                                        display[x+ (xPixelSizeScreen*y)] = 200;
                                    }
                                    else if((transparentColor != pixel) && (x < xPixelSizeScreen) && (y < yPixelSizeScreen))
                                    {
                                        display[x+ (xPixelSizeScreen*y)] = pixel;  
                                    }
                                }
                            }
                        }
                    }
                }       
            }  
        } 
                
         //UI rendering
        if(ui != NULL)
        {
            uint8_t buttonAmount = ui->getButtonAmount();
            uint8_t textAmount = ui->getTextAmount();
            uint8_t numberAmount = ui->getNumberAmount();
            uint8_t imageAmount = ui->getImageAmount();
            uint8_t rectAmount = ui->getRectAmount();
            uint8_t checkBoxAmount = ui->getCheckBoxAmount();
            uint8_t index;
            cursor_ui cursor = ui->getCursor();
                
            for(index = 0; index < buttonAmount;index++)
            {
                BUTTON *button = ui->getButton(index);
                if(button != NULL)
                {
                    button_ui settings = button->getButtonSettings();
                    uint16_t xSize = settings.position.x + settings.size.x;
                    uint16_t ySize = settings.position.y + settings.size.y;
                    uint16_t positionX = settings.position.x;
                    uint16_t positionY = settings.position.y;
                    uint16_t lengthText = strlen(settings.pText);
                    uint8_t heightFont = 0;

                    vector2 fontStart;
                    uint16_t highLightStartX = xSize; 
                    uint16_t highLightStartY = ySize;
                    getFontSize(settings.font,&heightFont);


                    fontStart.y = (ySize - (settings.size.y/2)) - heightFont/2;
                    fontStart.x = (xSize - (settings.size.x/2)) - (heightFont*lengthText)/2;


                    if(settings.highLightOn)
                    {
                        xSize += settings.highLightWidth;
                        ySize += settings.highLightWidth;
                        positionX -= settings.highLightWidth;
                        positionY -= settings.highLightWidth;
                    }

                    if((positionX < xPixelSizeScreen) && (positionX >=0) &&
                        (positionY < yPixelSizeScreen) && (positionY >=0) &&
                        (xSize < xPixelSizeScreen) && (ySize < xPixelSizeScreen) && (!settings.Hidden))
                    {
                        for(uint16_t yIndex = positionY; yIndex < ySize; yIndex++)
                        {                                        
                            for(uint16_t xIndex = positionX; xIndex < xSize; xIndex++)
                            {
                                if(settings.highLightOn && (xIndex < settings.position.x || xIndex >= highLightStartX ||
                                    yIndex < settings.position.y || yIndex >= highLightStartY))
                                {
                                    display[xIndex + (xPixelSizeScreen*yIndex)] = settings.highLightColor;  
                                }
                                else
                                {        
                                    display[xIndex + (xPixelSizeScreen*yIndex)] = settings.buttonColor;                                   
                                } 
                            }                                    
                        }
                        drawChars(settings.pText,lengthText,settings.font,settings.textColor,fontStart);    
                    }
                }
            }
                
            // ui images
            for(index = 0; index < imageAmount;index++)
            {
                IMAGE *image = ui->getImage(index);
                if(image != NULL)
                {
                    image_ui settings = image->getImageSettings();
                    uint8_t pixel = 0;
                    vector2 end;
                    end.x = settings.position.x+settings.size.x;
                    end.y = settings.position.y+settings.size.y; 
                    if(settings.pTexture != NULL && !settings.hidden)
                    {
                        for(uint16_t height = settings.position.y; height < end.y; height++)
                        {
                            uint16_t y = height - settings.position.y;
                            for(uint16_t width = settings.position.x; width < end.x; width++)
                            {   
                                uint16_t x = width - settings.position.x;
                                pixel = settings.pTexture[x +(settings.size.x*y)];
                                if(settings.transparentColor != pixel && (width < xPixelSizeScreen)
                                    && (height < yPixelSizeScreen))
                                {
                                    display[width+ (xPixelSizeScreen*height)] = pixel;  
                                }
                            }
                        }
                    }
                }                    
            }

            // ui checkBox
            for(index = 0; index < checkBoxAmount;index++)
            {
                CHECKBOX *check = ui->getCheckBox(index);
                if(check != NULL)
                {
                    checkBox_ui settings = check->getCheckSettings();
                    uint8_t pixel = 0;
                    vector2 end;
                    end.x = settings.position.x+SIZE_CHECKBOX;
                    end.y = settings.position.y+SIZE_CHECKBOX; 
                    if(!settings.hidden)
                    {
                        for(uint16_t height = settings.position.y; height < end.y; height++)
                        {
                            uint16_t y = height - settings.position.y;
                            for(uint16_t width = settings.position.x; width < end.x; width++)
                            {   
                                uint16_t x = width - settings.position.x;
                                pixel = settings.checkBox[x +(SIZE_CHECKBOX*y)];
                                if(TRANS_COLOR != pixel && (width < xPixelSizeScreen)
                                    && (height < yPixelSizeScreen))
                                {
                                    display[width+ (xPixelSizeScreen*height)] = pixel;  
                                }
                            }
                        }
                    }
                }                    
            }


            // ui rect
            for(index = 0; index < rectAmount;index++)
            {
                RECT *rect = ui->getRect(index);
                if(rect != NULL)
                {
                    rect_ui settings = rect->getRectSettings();
                    uint16_t upEndLine = settings.position.y + settings.lineWidth;
                    uint16_t downStartLine = settings.position.y+settings.size.y-settings.lineWidth;
                    uint16_t leftEndLine = settings.position.x+settings.lineWidth;
                    uint16_t rightStartLine = settings.position.x+settings.size.x-settings.lineWidth;
                    vector2 end;
                    end.x = settings.position.x+settings.size.x;
                    end.y = settings.position.y+settings.size.y;
                    if(!settings.hidden)
                    {
                        for(uint16_t height = settings.position.y; height < end.y; height++)
                        {
                            for(uint16_t width = settings.position.x; width < end.x; width++)
                            {      
                                if((width < xPixelSizeScreen) && (height < yPixelSizeScreen))
                                {   
                                    if((height < upEndLine) || (height >= downStartLine) ||
                                        (width < leftEndLine) || (width >= rightStartLine))
                                    {
                                        display[width+ (xPixelSizeScreen*height)] = settings.colorLine;
                                    }
                                    else if( width <= settings.fillArea)
                                    {
                                        display[width+ (xPixelSizeScreen*height)] = settings.colorFill;
                                    }
                                }
                            }
                        }
                    }
                }                    
            }

            // text
            for(index = 0; index < textAmount;index++)
            {
                TEXT *text = ui->getText(index);
                if(text != NULL)
                {
                    text_ui settings = text->getTextSettings();
                    uint16_t lengthText = strlen(settings.pText);
                    
                    if(settings.hidden == false)
                        drawChars(settings.pText,lengthText,settings.font,settings.textColor,settings.position);   
                }                   
            }


            //write numbers
            for(index = 0; index < numberAmount;index++)
            {
                    
                NUMBER *number = ui->getNumber(index);
                if(number != NULL)
                {
                    number_ui settings = number->getNumberSettings();
                    if(!settings.hidden)
                    {   
                        char str[11];
                        sprintf(str, "%d", settings.number);
                        drawChars(str,strlen(str),settings.font,settings.textColor,settings.position); 
                    }                       
                }                   
            }

            //cursor
            if(!cursor.hidden )
            {
                vector2 end;
                uint8_t height;
                uint8_t pixel = 0;
                uint8_t fontPixelx;
                uint8_t set = 0;
                bool draw = false;
                bool imageCursor = false;
                if(cursor.textureCursor != NULL)
                {
                    end = cursor.sizeTexture;
                    end.x += cursor.position.x;
                    end.y += cursor.position.y;
                    imageCursor = true;
                }
                else   
                {
                    getFontSize(FONT_10,&height); 
                    end.x = cursor.position.x+height;
                    end.y = cursor.position.y+height;
                    set = cursor.fontColor;
                }
                uint8_t shiftFont = height-1; 
                for(uint16_t yIndex = cursor.position.y; yIndex < end.y; yIndex++)
                {
                    uint16_t ySet = yIndex-cursor.position.y;
                    if(!imageCursor)
                    {
                        pixel = setPixelForChar(cursor.textCursor,FONT_10,ySet);
                    } 
                    fontPixelx = 0;
                    for(uint16_t xIndex = cursor.position.x; xIndex < end.x; xIndex++)
                    {
                        if(imageCursor)
                        {
                            uint16_t x = xIndex - cursor.position.x;                       
                            set = cursor.textureCursor[x +(cursor.sizeTexture.x*ySet)];
                            if(set != cursor.transparentColor)
                            {
                                draw = true;
                            }
                        }
                        else
                        {
                            if(1 & (pixel >> (shiftFont-fontPixelx)))
                            {
                                draw = true;
                            }
                            fontPixelx++;
                        }
                            
                        if(draw  && (xIndex < xPixelSizeScreen) &&(yIndex < yPixelSizeScreen))
                        {
                            display[xIndex + (xPixelSizeScreen*yIndex)] = set;
                            draw = false;       
                        }
                    }   
                } 
            }
        }

        //fps
        if(showFPS)
        {
            char str[3];
            vector2 pos(FPS_X_POSITION,FPS_Y_POSITION);
            sprintf(str, "%d", fps);
            
            drawChars(str,strlen(str), FONT_10, FPS_TEXT_COLOR, pos);         
        }   

   
    draw(display,(xPixelSizeScreen*yPixelSizeScreen));

    }
}