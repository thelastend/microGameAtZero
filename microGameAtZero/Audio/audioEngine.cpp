//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "audioEngine.h"
#include "../core/middleware.h"    
#include "beep.h"

volatile soundChannel AUDIOENGINE::channels[MAX_AUDIO_CHANNELS];
volatile uint8_t AUDIOENGINE::volumeMain;
volatile audioSampleRate_t AUDIOENGINE::sampleRate;
AUDIOENGINE* AUDIOENGINE::instance = 0;
volatile bool AUDIOENGINE::muteOn;
volatile uint32_t AUDIOENGINE::beepCount;
volatile uint32_t AUDIOENGINE::beepSize;


/**
 * @brief This function sets the audio output with the values of the channels with the
 *        adjusted volume.
 * 
 */
void IRAM_ATTR AUDIOENGINE::playSound()
{
    uint16_t value = 0;
    if(!muteOn)
    {
        for(uint8_t ii = 0; ii < MAX_AUDIO_CHANNELS;ii++)
        {
            if(channels[ii].playing && channels[ii].sound != nullptr)
            {
                value += channels[ii].sound[channels[ii].positionCount];
                value = value*channels[ii].volumeChannel/100;
                channels[ii].positionCount++;
                if( (channels[ii].positionCount %  channels[ii].size)==0 )
                {
                        channels[ii].positionCount = 4;
                        if(channels[ii].oneShot)
                            channels[ii].playing = false;
                }
            }
        }

        if(beepCount)
        {
            value = beep[beepCount];
            beepCount++;
            if(beepCount == beepSize)
            {
                setAudioSampleRate(sampleRate);
                startAudioTimer();
                beepCount = 0;
            }
        }

        value = value*volumeMain/100;

        if(value > 255)
            value = 255;

        
    }
    setAudioValue(value);
    
}


/**
 * @brief Construct a new AUDIOENGINE::AUDIOENGINE object
 * 
 */
AUDIOENGINE::AUDIOENGINE( )
{
    volumeMain = 0;
    beepCount = 0;
    beepSize = sizeof(beep);
    sampleRate = SAMPLE_22_KHZ;
    muteOn = false;


    if(setupAudio(sampleRate, this->playSound) == MICRO_GAME_AT_ZERO_OK)
        startAudioTimer();
}


/**
 * @brief This function turns off the selected channel for audio output.
 * 
 * @param channel selected channel (0 to 7)
 */
void AUDIOENGINE::stopPlaying(audioChannel_t channel){
    if(channel < MAX_AUDIO_CHANNELS)
    {
        if(channels[channel].playing && channels[channel].sound != nullptr)
        {
            channels[channel].playing = false;
        }
    }
}


/**
 * @brief This function sets the sample rate of the audio output.
 * 
 * @param sample the sample rate of the output (SAMPLE_16_KHZ, SAMPLE_22_KHZ or SAMPLE_44_KHZ)
 * @return MICRO_GAME_AT_ZERO_OK if everything's is okay and otherwise the error code
 */
microGameAtZero_err AUDIOENGINE::setSampleRate(audioSampleRate_t sample)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(sample < MAX_SAMPLE_RATE)
    {
        sampleRate = sample;
        error = setAudioSampleRate(sample);
    }
   
    return error;
}


/**
 * @brief This function returns the set sample rate.
 * 
 * @return SAMPLE_16_KHZ, SAMPLE_22_KHZ or SAMPLE_44_KHZ 
 */
audioSampleRate_t AUDIOENGINE::getSampleRate()
{
    return sampleRate;
}


/**
 * @brief This function starts the audio playback of the selected channel at the
 *        selected position, in the desired mode (one-shot or loop)
 * 
 * @param channel       the channel to be switched on
 * @param positionStart at which position the sound should be the start
 * @param oneShot       if true the sound is playing only once otherwise playing in a loop
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM if the selected channel is not in the range 0 to 7
 *                                          or no sound has been loaded into the channel
 */
microGameAtZero_err AUDIOENGINE::startPlaying(audioChannel_t channel, uint16_t positionStart, bool oneShot)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(channel < MAX_AUDIO_CHANNELS)
    {    
        if(channels[channel].playing )
        {
            error = CHANNEL_IS_PLAYING; 
        }
        else if(channels[channel].sound != nullptr)
        {
            channels[channel].playing = true;
            channels[channel].positionCount = positionStart;
            channels[channel].oneShot = oneShot;
            startAudioTimer();
            error = MICRO_GAME_AT_ZERO_OK; 
        }
    }
    return error;
}


/**
 * @brief This function starts the selected channel at the last position where it
 *        was stopped.
 * 
 * @param channel selected channel (0 to 7)
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM if the selected channel is not in the range 0 to 7
 * @return CHANNEL_IS_PLAYING    if the channel is already playing                                
 */
microGameAtZero_err AUDIOENGINE::continuePlay(audioChannel_t channel)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(channel < MAX_AUDIO_CHANNELS)
    {
        error = MICRO_GAME_AT_ZERO_OK;
        if(channels[channel].playing == false)
            channels[channel].playing = true;
        else
            error = CHANNEL_IS_PLAYING;   
    }
    return error;
}


/**
 * @brief This function sets the sound for the selected channel and volume.
 * 
 * @param channel   selected channel (0 to 7)
 * @param pSound    pointer to the sound array
 * @param volume    volume level to be set range 0 to 100
 * @param sizeSound length of the sound
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM if the selected channel is not in the range 0 to 7 or/and the volume is not
 *                                          in the range 0 to 100.
 */
microGameAtZero_err AUDIOENGINE::setChannel(audioChannel_t channel, const uint8_t *pSound, uint8_t volume, uint32_t sizeSound)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((channel < MAX_AUDIO_CHANNELS) && (volume <= MAX_VOLUME)) 
    {
        channels[channel].size = sizeSound;
        channels[channel].playing = false;
        channels[channel].sound = pSound;
        channels[channel].volumeChannel = volume;
        channels[channel].positionCount = 0;

        error = MICRO_GAME_AT_ZERO_OK;  
    }
    
    return error;
}


/**
 * @brief This function sets on the selected channel the desired volume.
 * 
 * @param channel   selected channel (0 to 7)
 * @param volume    volume level to be set range 0 to 100
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM if the selected channel is not in the range 0 to 7 or/and the volume is not
 *                                          in the range 0 to 100.
 */
microGameAtZero_err AUDIOENGINE::setVolumeChannel(audioChannel_t channel, uint8_t volume)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if((channel < MAX_AUDIO_CHANNELS) && (volume <= MAX_VOLUME))
    {
        channels[channel].volumeChannel = volume;
        error = MICRO_GAME_AT_ZERO_OK;
    }
    return error;
}


/**
 * @brief This function sets the main volume.
 * 
 * @param volume volume level to be set range 0 to 100
 * @return MICRO_GAME_AT_ZERO_OK is everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM if the selected volume is not in the range 0 to 100 
 */
microGameAtZero_err AUDIOENGINE::setMainVolume(uint8_t volume)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(volume <= MAX_VOLUME)
    {
        volumeMain = volume;
        error = MICRO_GAME_AT_ZERO_OK;
    }
    return error;
}


/**
 * @brief This function returns whether the selected  channel is switched on or not.
 * 
 * @param channel selected channel (0 to 7)
 * @return true if switched on
 * @return false if switched off
 */
bool AUDIOENGINE::isPlaying(audioChannel_t channel)
{
    bool playing = false;
    if(channel < MAX_AUDIO_CHANNELS)
        playing = channels[channel].playing;
    
    return playing;
}


/**
 * @brief This function starts playing a beep sound in the one-shot mode.
 * 
 */
void AUDIOENGINE::playBeep()
{
    beepCount = 1;
    setAudioSampleRate(SAMPLE_44_KHZ);
    startAudioTimer();
}


/**
 * @brief With this function, you can mute the audio output.
 * 
 * @param mute if true is muted otherwise not 
 */
void AUDIOENGINE::setMute(bool mute)
{
    muteOn = mute;
}

/**
 * @brief This function returns the mute status.
 * 
 * @return true is muted
 * @return false is not muted
 */
bool AUDIOENGINE::getMute()
{
    return muteOn;
}

/**
 * @brief This function returns the main volume level.
 * 
 * @return main volume level 
 */
microGameAtZero_err AUDIOENGINE::getMainVolume()
{
    return volumeMain;
}