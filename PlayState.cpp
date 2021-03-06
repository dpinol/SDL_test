//
//  PlayState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include <iostream>
#include "PlayState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "JewelBoard.h"
#include "MovingObject.h"
#include "ScorePanel.h"
#include <model/Match.h>

const std::string PlayState::s_playID = "PLAY";


static bool m_keyPpressed = false;
static bool m_paused = false;

class TNT : public MovingObject
{
public:
  TNT()
    :MovingObject("assets/spark.png", 60 * 1000, true, 0.2)
  {
    Trajectory trj = {
      { 265, 557},
      { 258, 553},
      { 256, 550},
      { 254, 546},
      { 252, 538},
      { 254, 526},
      { 255, 520},
      { 253, 517},
      { 249, 515},
      { 241, 512},
      { 227, 511},
      { 220, 510},
      { 217, 508},
      { 214, 504},
      { 208, 382},
      { 208, 382},
      { 208, 378},
      { 206, 376},
      { 205, 374},
      { 180, 372}
    };
    setTrajectory(trj);
    setAlphaOscillation(0.8);
    setRandomSize(0.3);
  }
};

PlayState::PlayState()
{
  ScorePanel* panel = new ScorePanel(TheGame::Instance()->getMatch());
  JewelBoard* board = new JewelBoard(TheGame::Instance()->getMatch());
  m_gameObjects.push_back(board);
  m_gameObjects.push_back(new TNT);
  m_gameObjects.push_back(panel);
}


void PlayState::update()
{
  if(m_loadingComplete && !m_exiting)
  {
    /*if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
      TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }*/

    //        if(TheInputHandler::Instance()->getButtonState(0, 8))
    //        {
    //            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    //        }

   /* if(TheGame::Instance()->getMatch().getPlayerLives() == 0)
    {
      TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }*/

    bool keyPpressed = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_P);
    if (keyPpressed && !m_keyPpressed)
      m_paused = !m_paused;
    m_keyPpressed = keyPpressed;
    if (!m_paused)
      //m_jewelBoard->update();
      GameState::update();
  }
}

void PlayState::render()
{
  if(m_loadingComplete)
  {

    /*   if(pLevel != 0)
    {
      pLevel->render();
    }
*/
    TheTextureManager::Instance()->draw("background", 0,0,
                                        755, 600);
    GameState::render();

    for(int i = 0; i < TheGame::Instance()->getMatch().getPlayerLives(); i++)
    {
      TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, nullptr, 0.0, 255);
    }
  }

  //m_jewelBoard->draw();
 // GameState::render();
}

bool PlayState::onEnterImpl()
{
  TheGame::Instance()->getMatch().restart();

  TheTextureManager::Instance()->load("assets/BackGround.jpg", "background");

  std::cout << "entering PlayState\n";
  return true;
}

bool PlayState::onExit()
{
  m_exiting = true;

  TheInputHandler::Instance()->reset();

  std::cout << "exiting PlayState\n";
  return true;
}
