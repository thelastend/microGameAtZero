//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "middleware.h"


/**
 * @brief This middleware function initialization the audio hardware.
 * 
 * @param sampleRate        audio sample rate
 * @param audioCallback     function pointer to the audio output control function
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupAudio(audioSampleRate_t sampleRate, timerCoreCallback audioCallback)
{
    return initAudio(sampleRate,audioCallback);
}


/**
 * @brief This middleware function starts the timer for the audio output.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err startAudioTimer()
{
    return startAudio();
}


/**
 * @brief This middleware function distributes the audio value to the audio driver.
 * 
 * @param value 8-bit audio output value
 * @return MICRO_GAME_AT_ZERO_OK everything is OK 
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err setAudioValue(uint8_t value)
{
    return setValue(value);
}


/**
 * @brief This middleware function distributes the sample rate value to the audio driver.
 * 
 * @param sampleRate new sample rate
 * @return MICRO_GAME_AT_ZERO_OK everything is OK 
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setAudioSampleRate(audioSampleRate_t sampleRate)
{
    return setSampleRate(sampleRate);
}

/**
 * @brief This middleware function initialization the timer hardware.
 * 
 * @param timerFunction     function pointer to the timer control function
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupTimer(timerCoreCallback timerFunction)
{
    return initTimer(timerFunction);
}


/**
 * @brief This middleware function starts the hardware timer.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err startTimer()
{
    return startMainTimer();
}


/**
 * @brief This middleware function initialization the battery hardware.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupBattery()
{
    return initBattery();
}


/**
 * @brief This middleware function returns the charge status of the battery.
 * @return the charge status of the battery in percent
 */
uint8_t batteryValue()
{
    return getBatteryValue();
}



/**
 * @brief This middleware function initialization the button hardware.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupButton()
{
    return initButton();
}


/**
 * @brief This middleware function returns whether the selected button is pressed.
 * 
 * @param selectButton the selected button
 * @return true if the selected button is press
 * @return false if the selected button is not press
 */
bool getInputButton(uint8_t  selectButton)
{
    return getButton(selectButton);
}



/**
 * @brief This middleware function returns whether the selected direction of the joypad is pressed.
 * 
 * @param direction direction of the joypad (up,down, left or right)
 * @return true if the selected direction of the joypad is press
 * @return false if the selected direction of the joypad is not press
 */
bool getInputJoyPad(uint8_t direction)
{
    return getJoyPad(direction);
}

/**
 * @brief This middleware function initialization the display hardware. 
 *
 * @param startX the x start position of the viewing area of the display
 * @param startY the y start adress of the viewing area of the display
 * @param endX   the x end position of the viewing area of the display
 * @param endY   the y end position of the viewing area of the display
 * @param speed  the transmission speed of the bus 
 * @param brightness brightness to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupDisplay(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY,
							 uint32_t speed, uint8_t brightness)
{
    return initDisplay(startX, startY, endX, endY, speed, brightness);
}


/**
 * @brief This middleware function connects the display to the bus.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err connectDisplay()
{
    return displayConnect();
}


/**
 * @brief This middleware function disconnects the display from the bus.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err disconnectDisplay()
{
    return displayDisconnect();
}


/**
 * @brief This middleware returns the connection status of the display.
 * 
 * @return true display is connected
 * @return false diplay is disconnected
 */
bool getDisplayConnection()
{
    return isDisplayConnected();
}


/**
 * @brief This middleware function sends the new display data to the driver.
 * 
 * @param pData   pointer to the data array that holds the values to be displayed
 * @param length the length of the data array
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err draw(uint8_t *pData, uint32_t length)
{
    return updateDisplay(pData,length);
}


/**
 * @brief This middlware function sends the new brightness value to the hardware driver.
 * 
 * @param brightness new brightness value to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setDisplayLight(uint8_t brightness)
{
    return setBrightness(brightness);
}


/**
 * @brief This middlware function returns the current brightness value.
 * 
 * @return current brightness value 
 */
microGameAtZero_err getDisplayLight()
{
    return getBrightness();
}


/**
 * @brief This middleware function sends the settings of the view area of the display to the hardware driver. 
 * 
 * @param startX the x start position of the view area
 * @param startY the y start position of the view area
 * @param endX   the x end position of the view area
 * @param endY   the y end position of the view area
 * @param mode SET_AREA_NO_SAVE the settings are not stored
 *             SET_AREA_SAVE the settings will be stored
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_NO_SAVE the selected mode is not known
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameters
 */
microGameAtZero_err setWindowArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t mode)
{
    return setArea(startX, startY, endX, endY, mode);
}


/**
 * @brief This middleware function fills the selected area with the chosen color.
 * 
 * @param startX the x start position of the rectangle
 * @param startY the y start position of the rectangle
 * @param endX   the x end position of the rectangle
 * @param endY   the y end position of the rectangle
 * @param color  the color to be filled with
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameters
 */
microGameAtZero_err fillRect(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t color)
{
    return fillArea(startX, startY, endX, endY, color);
}



/**
 * @brief This middleware function handles the process of sending the data to the sd card. 
 * 
 * @param pFileName pointer to the filename where the data should be written (max length MAX_LENGTH_NAME)
 * @param pData pointer to the data
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err sendDataSd(char *pFileName, char *pData)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INIT_ERROR;

    if(isDisplayConnected())
        disconnectDisplay();
    error = initSD();
    if(error == MICRO_GAME_AT_ZERO_OK)
    {
        error = writeTo(pFileName, pData);
        unmountSD();
    }

    if(!isDisplayConnected())
        displayConnect();

    return error;
}



/**
 * @brief This middlware function handles the process of reading the data from the sd card. 
 * 
 * @param pFileName pointer to the filename of the file to be read from (max fileName length MAX_LENGTH_NAME)
 * @param pBuffer pointer to the buffer where the data should be loaded
 * @param sizeBuffer size of the buffer
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter ( e.g fileName > MAX_LENGTH_NAME, pBuff == NULL ...)
 */
microGameAtZero_err readDataSd(char *pFileName, char *pBuffer, uint32_t sizeBuffer)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INIT_ERROR;

    if(isDisplayConnected())
        disconnectDisplay();
    error = initSD();
    if((error == MICRO_GAME_AT_ZERO_OK) && (pBuffer != NULL) && (pFileName != NULL))
    {
        error = readFrom(pFileName, pBuffer, sizeBuffer);
        unmountSD();
    }

    if(!isDisplayConnected())
        displayConnect();
    return error;
}


/**
 * @brief This middlware function returns a list of available files
 * 
 * @param files pointer to the file list
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error  
 */
microGameAtZero_err existedFiles(char *files[MAX_LENGTH_NAME])
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INIT_ERROR;
    if(isDisplayConnected())
        disconnectDisplay();

    error = initSD();
    if(error == MICRO_GAME_AT_ZERO_OK)
    {

        error = getFiles(files);
        unmountSD();
    }

    if(!isDisplayConnected())
        displayConnect();
    return error;
}


/**
 * @brief This middleware function is for processing and calling the driver for the
 *        UART initialization. 
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err setupUart()
{
    return initUart();
}


/**
 * @brief This middleware function sending the message over UART. 
 * 
 * @param pMsg pointer to the message to be sent
 * @return the number of transferred bytes
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM error
 */
microGameAtZero_err sendMsgUart(const char *pMsg)
{
    return sendUart(pMsg);
}