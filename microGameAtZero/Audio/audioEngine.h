#ifndef _AUDIOENGINE_MICROGAMEATZERO_
#define _AUDIOENGINE_MICROGAMEATZERO_

#include <stdint.h>
#include <stddef.h>
#include "../configMicroGameAtZero.h"
#include "../Driver/microGameAtZeroTargetSettings.h"
#include "../microGameAtZeroError.h"


#define MASK_CHANNEL0 0b00000001
#define MASK_CHANNEL1 0b00000010
#define MASK_CHANNEL2 0b00000100
#define MASK_CHANNEL3 0b00001000
#define CHANNEL_IS_PLAYING  1

/**
 * @brief Audio channel struct
 * 
 */
struct soundChannel
{
    const uint8_t *sound = nullptr;
    uint32_t size = 0;
    uint8_t volumeChannel = 0;
    bool playing = false;
    uint32_t positionCount = 0;
    bool oneShot = false;
};

/**
 * @brief enumeration of the Audio channels
 * 
 */
enum audioChannel_t {
    CHANNEL1 = 0,
    CHANNEL2 = 1,
    CHANNEL3 = 2,
    CHANNEL4 = 3,
    CHANNEL5 = 4,
    CHANNEL6 = 5,
    CHANNEL7 = 6,
    CHANNEL8 = 7,
    MAX_AUDIO_CHANNELS
};


/**
 * @brief Audio engine class
 * 
 */
class AUDIOENGINE {


public: 
    /**
    * @brief    This function returns the instance of the AUDIOENGINE. If no instance exists, 
    *           the function creates an instance of the AUDIOENGINE.
    * @return   AUDIOENGINE * pointer to the AUDIOENGINE instance 
    */
    static AUDIOENGINE* getInstance()
    {
        if (! instance)
        {
            instance = new AUDIOENGINE();
        }
        return instance;
    }
    ~AUDIOENGINE( );
    static void stopPlaying(audioChannel_t channle);
    static microGameAtZero_err startPlaying(audioChannel_t channle, uint16_t positionStart, bool oneShot);
    static microGameAtZero_err continuePlay(audioChannel_t channle);
    static microGameAtZero_err setSampleRate(audioSampleRate_t sample);
    static audioSampleRate_t getSampleRate();
    static microGameAtZero_err setChannel(audioChannel_t channle, const uint8_t *pSound, uint8_t volume, uint32_t sizeSound);
    static microGameAtZero_err setVolumeChannel(audioChannel_t channle, uint8_t volume);
    static microGameAtZero_err setMainVolume(uint8_t volume);
    static microGameAtZero_err getMainVolume();
    static bool isPlaying(audioChannel_t channle);
    static void playBeep();
    static void setMute(bool mute);
    static bool getMute();
    static void  playSound();


private:
    static AUDIOENGINE* instance;
    AUDIOENGINE( );
    volatile static soundChannel channels[MAX_AUDIO_CHANNELS];
    volatile static uint8_t volumeMain;
    volatile static uint32_t beepCount;
    volatile static uint32_t beepSize;
    volatile static audioSampleRate_t sampleRate;
    volatile static bool muteOn;
};


#endif