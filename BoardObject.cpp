//
//  SDLGameObject.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "BoardObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

BoardObject::BoardObject() :    GameObject(),
                                    m_bPlayedDeathSound(false),
                                    m_lastSafePos(0,0)
{
}

void BoardObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    // get position
    m_pixel = Vector2D(pParams->getX(),pParams->getY());
    
    // get drawing variables
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

// draw the object to the screen
void BoardObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                          m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void BoardObject::update()
{
    m_pixel += m_velocity;
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
    if (m_bDying)
      doDyingAnimation();
}

void BoardObject::doDyingAnimation()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));

    if(m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
        m_bDying = false;
    }
    m_dyingCounter++;
}


bool BoardObject::checkCollideTile(Vector2D newPos)
{
    if(newPos.getY() + m_height >= TheGame::Instance()->getGameHeight() - 32)
    {
        return false;
    }
    else
    {
        for(std::vector<TileLayer*>::iterator it = m_pCollisionLayers->begin(); it != m_pCollisionLayers->end(); ++it)
        {
            TileLayer* pTileLayer = (*it);
            std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
            
            Vector2D layerPos = pTileLayer->getPixel();
            
            int x, y, tileColumn, tileRow, tileid = 0;
            
            x = layerPos.getX() / pTileLayer->getTileSize();
            y = layerPos.getY() / pTileLayer->getTileSize();
            
            Vector2D startPos = newPos;
            startPos.setX(startPos.getX() + 15);
            startPos.setY(startPos.getY() + 20);
            Vector2D endPos(newPos.getX() + (m_width - 15), (newPos.getY()) + m_height - 4);
            
            for(int i = startPos.getX(); i < endPos.getX(); i++)
            {
                for(int j = startPos.getY(); j < endPos.getY(); j++)
                {
                    tileColumn = i / pTileLayer->getTileSize();
                    tileRow = j / pTileLayer->getTileSize();
                    
                    tileid = tiles[tileRow + y][tileColumn + x];
                    
                    if(tileid != 0)
                    {
                        return true;
                    }
                }
            }
        }
        
        return false;
        
    }
}
