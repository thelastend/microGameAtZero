#include "pong.h"

class LEVEL : public SCENE 
{

    public:
    LEVEL(){};
    ~LEVEL(){};
    virtual void sceneLogic(uint32_t deltaT);
};
                  
uint8_t ballImg[] = {
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

uint8_t pandlImg[] = {
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
  0xff,0xff,0xff,
};

uint8_t *pandlImgList[1];
uint8_t *ballList[1];

MICROGAMEATZERO *game;
AUDIOENGINE* audio;
NUMBER* countOne;
NUMBER* countTwo;
TEXT* playerNameOne;
LEVEL* pong;
RigidBody* ball;
vector2 ballVel(150,-150);
UI table;
KinectBody* playOne;
KinectBody* playTwo;

char keyInputText[50] = {"playOne"};
               
void LEVEL::sceneLogic(uint32_t deltaT)
{
  static bool keyShow = false;
  vector2 panlOne;
  vector2 panltwo;


  if(!keyShow)
  {
    objectSettings one = playOne->getValues();
    objectSettings two = playTwo->getValues();
    vector2 collision;

    if(game->getJoyPad(UP))
    {
      if((one.position.y) > 0)
      {
        panlOne.set(0,-10);
      }
    }
    else if(game->getJoyPad(DOWN))
    {
      if((one.position.y +10) < 230)
      {
        panlOne.set(0,10);
      }
    }


    if(game->getButton(A_BUTTON))
    {
      if((two.position.y) > 0)
      {
        panltwo.set(0,-10);
      }
    }
    else if(game->getButton(B_BUTTON))
    {
      if((two.position.y +10) < 230)
      {
        panltwo.set(0,10);
      }
    }

    if(game->getButton(SELECT))
    {
      if(!keyShow)
      {
        table.keyBoardUp("Pong",keyInputText,100);
        keyShow = true;
      }
    }

    if(game->getButton(START))
    {
      game->loadScene(SELECT_SCENE);
    }

    playOne->move(panlOne);
    playTwo->move(panltwo);

    objectSettings valueBal = ball->getValues();
    if(valueBal.position.x > 240)
    {
      ballVel.x = -250;
      countOne->changeNumber(countOne->getNumber()+1);
      audio->playBeep();
    }
    else if(valueBal.position.x < 0)
    {
      ballVel.x = 250;
      countTwo->changeNumber(countTwo->getNumber()+1);
      audio->playBeep();
    }
    if(valueBal.position.y > 238)
    {
      ballVel.y = -250;
    }
    else if(valueBal.position.y < 0 )
    {
      ballVel.y = 250;
    }

    collision = game->getCollision(playOne,ball);
    if(collision.x != 0)
    {
      ballVel.x = 250;
    }

    
    collision = game->getCollision(playTwo,ball);
    if(collision.x != 0)
    {
      ballVel.x = -250;
    }


    physicParam ballPhysic;
    ballPhysic.velocity = ballVel;
    ball->setPhysic(ballPhysic); 
  } 
  else
  {
    
    if(table.inputTextKeyBoard(keyInputText))
    {
      keyShow = false;
    }
  }
  

}

void setupPong()
{ 
    number_ui settingNumb;
    vector2 numbPos(60,15);
    pong = new LEVEL();
    playOne = new KinectBody();
    playTwo = new KinectBody();
    ball = new RigidBody();

    vector2 pandlPosOne(30,55);
    vector2 pandlPosTwo(210,55);
    vector2 pandlSize(3,20);
    vector2 playNamePosition(10,0);

    pandlImgList[0] = pandlImg;
    ballList[0] = ballImg;

    vector2 zero(0,0);
    playOne->setTexture(pandlSize,pandlImgList,pandlPosOne,0,0x00);
    playTwo->setTexture(pandlSize,pandlImgList,pandlPosTwo,0,0x00);
    playOne->setupCollisionWindow(zero,pandlSize,(collisionType )GROUND_AND_WALL);
    playTwo->setupCollisionWindow(zero,pandlSize,(collisionType )GROUND_AND_WALL);

    
    vector2 posBall(50,50);
    vector2 sizeBall(3,3);

    ball->setTexture(sizeBall,ballList,posBall,5,0);
    ball->setupCollisionWindow(zero,sizeBall,(collisionType )GROUND_AND_WALL);
    physicParam ballPhysic;
    posBall.y = 100;
    ballPhysic.velocity = ballVel;
    ball->setPhysic(ballPhysic);

    pong->addKinect(playOne);
    pong->addKinect(playTwo);
    pong->addRigid(ball);


    settingNumb.font = FONT_10;
    settingNumb.hidden = false;
    settingNumb.number = 0;
    settingNumb.position = numbPos;
    settingNumb.textColor = 0xff;
    countOne = new NUMBER(settingNumb);

    numbPos.x = 180;
    settingNumb.position = numbPos;
    countTwo = new NUMBER(settingNumb);

    table.addNumber(countOne);
    table.addNumber(countTwo);


    text_ui settingText;
    settingText.font = FONT_10;
    settingText.textColor = 0xFF;
    settingText.pText = keyInputText;
    settingText.position = playNamePosition;

    playerNameOne = new TEXT(settingText);
    table.addText(playerNameOne);

    pong->addUI(&table);

    game = MICROGAMEATZERO::getInstance();
    audio = AUDIOENGINE::getInstance();
    game->addNewScene(pong);
}