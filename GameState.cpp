/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 01/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "GameState.h"
#include "GameObject.h"
#include <utils/Effect.h>

GameState::GameState()
  : m_loadingComplete(false),
    m_exiting(false),
    m_effects(new dani::CompositeEffect)
{

}

GameState::~GameState()
{

}

void GameState::resume()
{

}

bool GameState::onEnter()
{
  bool ret = onEnterImpl();
  m_loadingComplete = true;
  return ret;
}

void GameState::render()
{
  if(m_loadingComplete)
  {
    for(GameObject * o: m_gameObjects)
    {
      o->draw();
    }
  }
}

void GameState::update()
{
  if(m_loadingComplete)
  {
    m_effects->update();
    for(GameObject * o: m_gameObjects)
    {
      o->update();
    }
  }
}


