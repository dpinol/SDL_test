//
//  SDLGameObject.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 19/01/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "PersistedObject.h"
#include "TextureManager.h"
#include "Game.h"

PersistedObject::PersistedObject() :    GameObject()
{
}

void PersistedObject::load(std::unique_ptr<LoaderParams> const &pParams)
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
void PersistedObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                          m_width, m_height, m_currentRow, m_currentFrame, 0, m_angle, m_alpha);
}

// apply velocity to current position
void PersistedObject::update()
{
    m_pixel += m_velocity;
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
    if (m_bDying)
      doDyingAnimation();
}

void PersistedObject::doDyingAnimation()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000/ 10)) % m_numFrames));

    if(m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
        m_bDying = false;
        m_dyingCounter = 0;
    }
    m_dyingCounter++;
}


