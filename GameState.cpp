/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 01/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "GameState.h"
#include "GameObject.h"

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
      for(int i = 0; i < m_gameObjects.size(); i++)
      {
          m_gameObjects[i]->draw();
      }
  }
}

void GameState::update()
{
  if(m_loadingComplete)
  {
      for(int i = 0; i < m_gameObjects.size(); i++)
      {
          m_gameObjects[i]->draw();
      }
  }
}


