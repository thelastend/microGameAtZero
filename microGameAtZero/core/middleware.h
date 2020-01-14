
#include "../configMicroGameAtZero.h"
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"

#ifdef ODROIDGO
#include "../Driver/OdroidGoDriver/audioTimerDriverOdroidGo.h"
#include "../Driver/OdroidGoDriver/batteryDriverOdroidGo.h"
#include "../Driver/OdroidGoDriver/buttonDriverOdroidGo.h"
#include "../Driver/OdroidGoDriver/displayDriverOdroidGo.h"
#include "../Driver/OdroidGoDriver/sdDriverOdroidGo.h"
#include "../Driver/OdroidGoDriver/uartDriverOdroidGo.h"
#endif

/*Audio*/
microGameAtZero_err setupAudio(audioSampleRate_t sampleRate, timerCoreCallback audioCallback);
microGameAtZero_err startAudioTimer();
microGameAtZero_err setAudioValue(uint8_t value);
microGameAtZero_err setAudioSampleRate(audioSampleRate_t sampleRate);

/*Timer*/
microGameAtZero_err setupTimer(timerCoreCallback timerFunction);
microGameAtZero_err startTimer();

/*Battery*/
microGameAtZero_err setupBattery();
uint8_t             batteryValue();

/*Input*/
microGameAtZero_err setupButton();
bool              getInputButton(uint8_t  selectButton);
bool              getInputJoyPad(uint8_t direction);

/*Display*/
microGameAtZero_err setupDisplay(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY,
							 uint32_t speed, uint8_t brightness);
microGameAtZero_err connectDisplay();
microGameAtZero_err disconnectDisplay();
bool				getDisplayConnection();
microGameAtZero_err draw(uint8_t *pData, uint32_t length);
microGameAtZero_err setDisplayLight(uint8_t brightness);
microGameAtZero_err getDisplayLight();
microGameAtZero_err setWindowArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t mode);
microGameAtZero_err fillRect(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t color);

/*SD Card*/
microGameAtZero_err sendDataSd(char *pFileName, char *pData);
char*               readDataSd(char *pFileName);
microGameAtZero_err existedFiles(char *files[MAX_LENGTH_NAME]);

/*UART*/
microGameAtZero_err setupUart();
microGameAtZero_err sendMsgUart(const char *pMsg);



