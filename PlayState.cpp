//
//  PlayState.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include <iostream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "JewelBoard.h"

const std::string PlayState::s_playID = "PLAY";

PlayState::PlayState()
{
    m_jewelBoard = new JewelBoard();
}

void PlayState::update()
{
  if(m_loadingComplete && !m_exiting)
  {
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
      TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    //        if(TheInputHandler::Instance()->getButtonState(0, 8))
    //        {
    //            TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    //        }

    if(TheGame::Instance()->getPlayerLives() == 0)
    {
      TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }


    m_jewelBoard->update();
  }
}

void PlayState::render()
{
  if(m_loadingComplete)
  {
    GameState::render();

 /*   if(pLevel != 0)
    {
      pLevel->render();
    }
*/
    TheTextureManager::Instance()->draw("background", 0,0,
                                        755, 600);

    for(int i = 0; i < TheGame::Instance()->getPlayerLives(); i++)
    {
      TheTextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
    }
  }

  m_jewelBoard->draw();
}

bool PlayState::onEnterImpl()
{
  TheGame::Instance()->setPlayerLives(3);

  TheTextureManager::Instance()->load("assets/BackGround.jpg", "background", TheGame::Instance()->getRenderer());

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
