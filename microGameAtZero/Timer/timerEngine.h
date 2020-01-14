#ifndef _TIMERENGINE_MICROGAMEATZERO_
#define _TIMERENGINE_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include <climits>
#include "../configMicroGameAtZero.h"
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"


/**
 * @brief structure of the timer settings.
 * 
 */
struct timerSettings {
    uint8_t timerId = 0;
    uint16_t timerValue = 0;
    timerCallback functionCall = NULL;
};


/**
 * @brief TIMERENGINE class
 * 
 */
class TIMERENGINE {

public:
    static TIMERENGINE* getInstance()
    {
        if (! instance)
        {
            instance = new TIMERENGINE();
        }
        return instance;
    }
    ~TIMERENGINE();
    microGameAtZero_err init();
    microGameAtZero_err addTimer(timerSettings settings);
    microGameAtZero_err removeTimer(uint8_t timerID);
    void setupCoreTimer(timerCallback timerFunction, uint8_t fps);
    void startUp();
    

private:
    static TIMERENGINE *instance;
    static bool initTimer;
    TIMERENGINE();
    static ATTR_RAM void mainTimer();
    static timerSettings timerList[MAX_TIMERS];
    static uint8_t freeTimer[MAX_TIMERS];
    static uint8_t numberOfTimers;
    static timerCallback coreCallback;
    static uint16_t coreTimeFps;
    static uint32_t deltaTime;
};
#endif