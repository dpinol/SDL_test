//
//  ObjectLayer.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 10/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "ObjectLayer.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

ObjectLayer::~ObjectLayer()
{
  for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
  {
    delete (*it);
  }
  m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{

  //    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

  // iterate through the objects

  for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
  {
    if((*it)->getPosition().getY() +  (*it)->getHeight() > 0) //TheGame::Instance()->getGameWidth())
    {
      (*it)->setUpdating(true);
      (*it)->update();
    }
    else
    {
      {
        (*it)->setUpdating(false);
      }
    }

    // check if dead or off screen
    if((*it)->dead() || (*it)->getPosition().m_y > TheGame::Instance()->getGameHeight())
    {
      std::cout << "deleting";
      delete * it;
      it = m_gameObjects.erase(it); // erase from vector and get new iterator
    }
    else
    {
      ++it; // increment if all ok
    }

  }

  //#endif
}

void ObjectLayer::render()
{
  for(int i = 0; i < m_gameObjects.size(); i++)
  {
    
    m_gameObjects[i]->draw();

  }
}
