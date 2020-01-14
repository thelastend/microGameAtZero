#ifndef _SHOOT_
#define _SHOOT_

#include <stdint.h>
#include "selectMenu.h"

#define NUMBER_ASTROID 5
#define MAX_LIFE       3
#define GAME_OVER "GAME OVER"
#define PRESS_SELECT "press select for new game"
#define FILE_NAME   "highscore"
#define HIGHSCORE   "HIGHSCORE: "
#define CURRENTSCORE  "SCORE: "

class SHOOTER : public SCENE 
{

    public:
    SHOOTER();
    ~SHOOTER();
    virtual void sceneLogic(uint32_t deltaT);

    private:
    MICROGAMEATZERO *game;
    void newAstroids();
    AUDIOENGINE* audio;
    UI playerInfo;
    KinectBody* player;
    RigidBody *astroid[NUMBER_ASTROID];
    uint8_t *shipImage[2]; 
    uint8_t *bulletImage[1];
    uint8_t *astroidImage[1];
    RigidBody *bullets[3];
    uint8_t lifeCount;
    uint8_t astroCount;
    IMAGE   *lifeImage[MAX_LIFE];
    TEXT    *gameOver;
    TEXT    *newGameText;
    TEXT    *highScoreText;
    TEXT    *scoreText;
    NUMBER  *numbHighScore;
    NUMBER  *currentScore;
    uint16_t highScoreCount;
    uint16_t currentScoreCount;
    uint8_t *explosionAnimation[5];
};

#endif