#include "shooter.h"
#include "shootImage.h"
#include <stdlib.h>
#include "sounds.h"
              


SHOOTER::SHOOTER()
{
    player = new KinectBody();
    game = MICROGAMEATZERO::getInstance();
    audio = AUDIOENGINE::getInstance();
    vector2 playerSize(32,32);
    vector2 zero;
    vector2 playerPosition(104,180);
    vector2 lifePosition(10,10);
    vector2 lifeSize(9,9);
    image_ui lifeSetting;
    text_ui textSetting;
    vector2 textPos(25,110);
    vector2 scorNumPos(200,5);
    number_ui scorSetting;
    char data[20];

    currentScoreCount = 0;
    highScoreCount = 0;

    audio->setChannel(CHANNEL2,hit,80,sizeof(hit));
    audio->setChannel(CHANNEL4,explosion,80,sizeof(explosion));

    if(game->loadFile(FILE_NAME,data,sizeof(data)) == MICRO_GAME_AT_ZERO_OK)
        highScoreCount = atoi(data);
        
    
    explosionAnimation[0] = expl_1;
    explosionAnimation[1] = expl_2;
    explosionAnimation[2] = expl_3;
    explosionAnimation[3] = expl_4;
    explosionAnimation[4] = expl_5;

    shipImage[0] = ship;
    shipImage[1] = expl_5;
    player->setSprite(playerSize,shipImage,playerPosition,0,0xFF);
    player->setAnimation(explosionAnimation,5,1,0xFF);
    player->setupCollisionWindow(zero,playerSize,PLAYER);
    this->addKinect(player); 

    bulletImage[0] = bullet;

    astroidImage[0] = asteroid;
    for(uint8_t index = 0; index < 3;index++)
    {
        bullets[index] = NULL;
    }

    for(uint8_t index = 0; index < NUMBER_ASTROID;index++)
    {
        astroid[index] = NULL;
    }

    lifeSetting.size = lifeSize;
    lifeSetting.pSprite = life;
    lifeSetting.transparentColor = 0xff;
    for(uint8_t index = 0; index < MAX_LIFE; index++)
    {
        lifeSetting.position = lifePosition;
        lifeImage[index] = new IMAGE(lifeSetting);
        playerInfo.addImage(lifeImage[index]);
        lifePosition.x += 15;   
    }

    textSetting.position = textPos;
    textSetting.font = FONT_20;
    textSetting.hidden = true;
    textSetting.pText = GAME_OVER;
    textSetting.textColor = 0xff;

    gameOver = new TEXT(textSetting);
    playerInfo.addText(gameOver);


    textPos.y += 25;
    textPos.x = 0; 
    textSetting.position = textPos;
    textSetting.font = FONT_10;
    textSetting.pText = PRESS_SELECT;
    newGameText = new TEXT(textSetting);
    playerInfo.addText(newGameText);

    textPos.y = 5;
    textPos.x = 100;
    textSetting.hidden = false;
    textSetting.position = textPos;   
    textSetting.pText = HIGHSCORE;
    highScoreText = new TEXT(textSetting);
    playerInfo.addText(highScoreText);

    textPos.y = 15;
    textPos.x = 100; 
    textSetting.position = textPos;   
    textSetting.pText =    CURRENTSCORE;
    scoreText = new TEXT(textSetting);
    playerInfo.addText(scoreText);


    scorSetting.font = FONT_10;
    scorSetting.hidden = false;
    scorSetting.number = highScoreCount;
    scorSetting.position = scorNumPos;
    scorSetting.textColor = 0xff;
    numbHighScore = new NUMBER(scorSetting);
    playerInfo.addNumber(numbHighScore);

    scorNumPos.y = 15;
    scorSetting.number = currentScoreCount;
    scorSetting.position = scorNumPos;
    scorSetting.textColor = 0xff;
    currentScore = new NUMBER(scorSetting);   
    playerInfo.addNumber(currentScore);

    newAstroids();
    this->addUI(&playerInfo);
    this->setBackgroundColor(0x02);
    lifeCount = 3;
    astroCount = NUMBER_ASTROID;


   
}

SHOOTER::~SHOOTER()
{
    
}

void SHOOTER::newAstroids()
{
    vector2 velocity(10,0);
    vector2 astroPosition(20,30);
    vector2 astroSize(17,16);
    vector2 zero;
    physicParam astroidPhysic;
    astroidPhysic.velocity = velocity;
    astroidPhysic.gravity = 10;
    astroCount = NUMBER_ASTROID;
    for(uint8_t index = 0; index < NUMBER_ASTROID; index++)
    {
        if(astroid[index] != NULL)
        {
            this->removeRigid(astroid[index]);
            astroid[index] = NULL;
        }
        astroid[index] = new RigidBody();
        astroid[index]->setSprite(astroSize,astroidImage,astroPosition,10,0xff);
        astroid[index]->setupCollisionWindow(zero,astroSize,(collisionType)(ENEMEY | PLAYER));
        astroPosition.x += 40;
        astroid[index]->setPhysic(astroidPhysic);
        this->addRigid(astroid[index]);
    }  

}
               
void SHOOTER::sceneLogic(uint32_t deltaT)
{
    static uint8_t countShootBreak = 0;
    static bool shootBreak = false;
    vector2 position;
    objectSettings plyPos = player->getValues();
    static bool explosion = true; 

    
    if(lifeCount > 0)
    {

        if(game->getJoyPad(LEFT))
        {
            if((plyPos.position.x-4) > 0)
            {
                position.x =-4;

            }
        }
        else if(game->getJoyPad(RIGHT))
        {
            if((plyPos.position.x +4) < 200)
            {
            position.x =4;
            }

        }


        for(uint8_t index = 0; index < NUMBER_ASTROID; index++)
        {
            if(astroid[index] != NULL)
            {
                objectSettings astroValues = astroid[index]->getValues();
                vector2 velocity(10,0);
                vector2 col = game->getCollision(astroid[index],player);
                if(col.x != 0 && col.y != 0)
                {
                    lifeCount--;
                    astroCount--;
                    playerInfo.setHiddenImage(lifeCount,true);
                    this->removeRigid(astroid[index]);
                    astroid[index] = NULL;
                }
                if(astroValues.position.x > (60 +40*index))
                {
                    velocity.x = -100;
                    astroid[index]->setVelocity(velocity);
                }
                else if(astroValues.position.x < (5+40*index))
                {
                    astroid[index]->setVelocity(velocity);                
                }
                else if(astroValues.position.y > MAX_HEIGHT_DISPLAY )
                {
                    newAstroids();
                    break;
                }
            }
        }
        



        for(uint8_t index = 0; index < 3;index++)
        {
            if(bullets[index] != NULL)
            {
                objectSettings bullValues = bullets[index]->getValues();
                if(bullValues.position.y < 0)
                {
                    this->removeRigid(bullets[index]);
                    bullets[index] = NULL;
                }
                else
                {
                    vector2 col;
                    for(uint8_t ii = 0; ii < NUMBER_ASTROID; ii++)
                    {
                        if(astroid[ii] != NULL)
                        {
                            col = game->getCollision(bullets[index],astroid[ii]);
                            if(col.x != 0 && col.y != 0)
                            {
                                currentScoreCount++;
                                currentScore->changeNumber(currentScoreCount);
                                this->removeRigid(bullets[index]);
                                bullets[index] = NULL;
                                this->removeRigid(astroid[ii]);
                                astroid[ii] = NULL;
                                astroCount--;
                                audio->startPlaying(CHANNEL2,0,true);
                                break;
                            }
                        }
                    }
                }
            }
        }
        

        if((game->getButton(B_BUTTON) || game->getButton(A_BUTTON)) && !shootBreak)
        {
            for(uint8_t index = 0; index < 3;index++)
            {
                if(bullets[index] == NULL)
                {
                    vector2 sizeBullet(5,7);
                    vector2 bulletPosition;
                    vector2 zero;
                    vector2 vel(0,-300);
                    bulletPosition.set(plyPos.position);
                    bulletPosition.x += 14;

                    bullets[index] = new RigidBody();
                    bullets[index]->setSprite(sizeBullet,bulletImage,bulletPosition,0,0xFF);
                    bullets[index]->setupCollisionWindow(zero,sizeBullet,ENEMEY);
                    physicParam bulletPhysic;
                    bulletPhysic.velocity = vel;
                    bullets[index]->setPhysic(bulletPhysic);
                    this->addRigid(bullets[index]);
                    break;
                }
            }
            shootBreak = true;
        }

        if(shootBreak)
        {
            countShootBreak++;
            if(countShootBreak == 10)
            {
                countShootBreak = 0;
                shootBreak = false;
            }
        }

        if(game->getButton(START))
        {
            game->loadScene(SELECT_SCENE);
        }

        if(astroCount == 0)
            newAstroids();
        
        player->move(position);
    }
    else
    {
        if(explosion)
        {
            audio->startPlaying(CHANNEL4,0,true);
            explosion = false;
            player->startAnimation(0, true);
        }
        
        if(player->animationStatus() == -1)
        {
            player->setShowSprite(1);
        }
        
        if(currentScoreCount > highScoreCount)
        {
            highScoreCount = currentScoreCount;
            numbHighScore->changeNumber(highScoreCount);
            char str[11];
            sprintf(str, "%d", currentScoreCount);
            game->saveFile(FILE_NAME,str);
        }

        playerInfo.setHiddenText(0,false);
        playerInfo.setHiddenText(1,false);

        for(uint8_t index = 0;index < 3;index++)
        {
            if(bullets[index] != NULL)
            {
                this->removeRigid(bullets[index]);
                bullets[index] = NULL;
            
            }
        }
        for(uint8_t index = 0;index < NUMBER_ASTROID;index++)
        {
            if(astroid[index] != NULL)
            {
                this->removeRigid(astroid[index]);
                astroid[index] = NULL;
            
            }
        }

        if(game->getButton(SELECT))
        {
            player->stopAnimation();
            player->setShowSprite(0);
            newAstroids();
            currentScoreCount = 0;
            currentScore->changeNumber(currentScoreCount);
            player->setHidden(false);
            playerInfo.setHiddenText(0,true);
            playerInfo.setHiddenText(1,true);
            lifeCount = MAX_LIFE;
            explosion = true;
            for(uint8_t index = 0;index < MAX_LIFE; index++)
            {
                playerInfo.setHiddenImage(index,false);
            }
        }

        if(game->getButton(START))
        {
            game->loadScene(SELECT_SCENE);
        }

    }
    
  
  
}

