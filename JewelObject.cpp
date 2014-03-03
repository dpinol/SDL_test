//
//  SDLGameObject.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "JewelObject.h"

#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

JewelObject::JewelObject(Jewel &jewel) :    m_model(&jewel)
{
    m_pixel = Vector2D(0,0);
    m_currentRow = 0;
    //we don't use it so far
    m_currentFrame = -1; //jewel.getColor();

    // get drawing variables
    m_width = 35;
    m_height = 35;
    m_textureID = "jewels";
}

Jewel& JewelObject::getModel()
{
  return *m_model;
}


void JewelObject::load(std::unique_ptr<LoaderParams> const &pParams)
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
void JewelObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                          m_width, m_height, m_currentRow, getModel().getColor(),
                                          TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void JewelObject::update()
{
}


void JewelObject::setMovement(JewelMove const &m)
{

}


bool JewelObject::checkCollideTile(Vector2D newPos)
{
    if(newPos.m_y + m_height >= TheGame::Instance()->getGameHeight() - 32)
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
            startPos.m_x += 15;
            startPos.m_y += 20;
            Vector2D endPos(newPos.m_x + (m_width - 15), (newPos.m_y) + m_height - 4);
            
            for(int i = startPos.m_x; i < endPos.m_x; i++)
            {
                for(int j = startPos.m_y; j < endPos.m_y; j++)
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

void JewelObject::kill()
{
  m_bDying = true;
}

