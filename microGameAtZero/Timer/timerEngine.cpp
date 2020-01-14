//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "timerEngine.h"
#include "../core/middleware.h"


TIMERENGINE* TIMERENGINE::instance;
bool TIMERENGINE::initTimer;
timerSettings TIMERENGINE::timerList[MAX_TIMERS];
uint8_t TIMERENGINE::freeTimer[MAX_TIMERS];
uint8_t TIMERENGINE::numberOfTimers;
timerCallback TIMERENGINE::coreCallback;
uint16_t TIMERENGINE::coreTimeFps;
uint32_t TIMERENGINE::deltaTime;


/**
 * @brief Destroy the TIMERENGINE::TIMERENGINE object
 * 
 */
TIMERENGINE::~TIMERENGINE()
{
    coreCallback = NULL;
    for(uint8_t ii = 0; ii < MAX_TIMERS;ii++)
    {
        timerList[ii].functionCall = NULL;
    }
}


/**
 * @brief Construct a new TIMERENGINE::TIMERENGINE object
 * 
 */
TIMERENGINE::TIMERENGINE()
{
    initTimer = false;
    coreCallback = NULL;
    coreTimeFps = 10;
}


/**
 * @brief This function initializes the timer engine.
 * 
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR initialisation error
 */
microGameAtZero_err TIMERENGINE::init()
{
    microGameAtZero_err initError = MICRO_GAME_AT_ZERO_INIT_ERROR;
    if(setupTimer(instance->mainTimer) == MICRO_GAME_AT_ZERO_OK)
    {
        initError = MICRO_GAME_AT_ZERO_OK;
        initTimer = true;
        numberOfTimers = 0;
        deltaTime = 0;
        memset(freeTimer,0,MAX_TIMERS);
    }
    return initError;
}


/**
 * @brief This function starts the main timer of the engine.
 * 
 */
void TIMERENGINE::startUp()
{
    startTimer();
}


/**
 * @brief This function is the interrupt function of the main timer and handles the timer callbacks. 
 *        (is called automatically and should not be called by the user)
 * 
 */
void ATTR_RAM TIMERENGINE::mainTimer()
{
    deltaTime++;

    if((deltaTime % coreTimeFps) == 0)
    {
        if(coreCallback != NULL)
        {
            coreCallback(coreTimeFps);
        }
    }

    for(uint8_t index = 0; index < MAX_TIMERS;index++)
    {
        if(timerList[index].timerId > 0)
        {
            if((deltaTime % timerList[index].timerValue) == 0)
            {
                timerList[index].functionCall(timerList[index].timerValue);
            }   
        } 
    }

    if(deltaTime == ULONG_MAX)
    {
        deltaTime =0;
    }
}

/**
 * @brief This function adds a new timer to the timer engine.
 * 
 * @param settings settings of the timer to be add
 * @return position of the timer in the array (identification number).
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR is no more space for a new timer
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR initialisation error
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err  TIMERENGINE::addTimer(timerSettings settings)
{
    microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    bool idExist = false;
    if(initTimer)
    {
        if(numberOfTimers < MAX_TIMERS)
        {
            for(uint8_t existIndex = 0; existIndex < MAX_TIMERS; existIndex++)
            {
                if(settings.timerId == timerList[existIndex].timerId)
                {
                    idExist = true;
                }
            }
            if(!idExist)
            {
                for(uint8_t index = 0; index < MAX_TIMERS; index++)
                {
                    if(freeTimer[index] == 0)
                    {
                        timerList[numberOfTimers].functionCall = settings.functionCall;
                        timerList[numberOfTimers].timerId = settings.timerId;
                        timerList[numberOfTimers].timerValue = settings.timerValue;
                        freeTimer[index] = 1;
                        addError = index;
                        break;
                    }
                }
                numberOfTimers++;
            }
        }
        else
        {
            addError = MICRO_GAME_AT_ZERO_FULL_ERROR;
        }
    }
    else
    {
        addError = MICRO_GAME_AT_ZERO_INIT_ERROR;
    }
    
    
    return addError;
}


/**
 * @brief This function removes the timer on the passed position.
 * 
 * @param timerID index of the timer to be remove
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err  TIMERENGINE::removeTimer(uint8_t timerID)
{
    microGameAtZero_err removeError = MICRO_GAME_AT_ZERO_INVALID_PARAM;


     for(uint8_t index = 0; index < MAX_TIMERS; index++)
    {
        if(timerList[numberOfTimers].timerId == timerID)
        {
            timerList[numberOfTimers].functionCall = NULL;
            timerList[numberOfTimers].timerId = 0;
            timerList[numberOfTimers].timerValue = 0;
            freeTimer[index] = 0;
            removeError = MICRO_GAME_AT_ZERO_OK;
            numberOfTimers--;
            break;
        }
    }
    return removeError;
}


/**
 * @brief This function setups the core timer with the desired fps rate and the callback function.
 * 
 * @param timerFunction callback function to be called after the time has expired
 * @param fps fps to be set 
 */
void TIMERENGINE::setupCoreTimer(timerCallback timerFunction, uint8_t fps)
{
    coreCallback = timerFunction;
    coreTimeFps = 1000/fps; //get milliseconds 

}