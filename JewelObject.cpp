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

JewelObject::JewelObject(Jewel &jewel) :
  m_model(&jewel),
  m_isFalling(false)
{
    m_pixel = Vector2D(0,0);
    m_currentRow = 0;
    //we don't use it so far
    m_currentFrame = -1; //jewel.getColor();

    // get drawing variables
    m_width = WIDTH;
    m_height = HEIGHT;
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
    if(getModel().getColor() != Jewel::NO_COLOR && !m_bDying)
      TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                          m_width, m_height, m_currentRow, getModel().getColor());
                                          //TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void JewelObject::update()
{
}


void JewelObject::setMovement(JewelMove const &m)
{

}



void JewelObject::kill()
{
  m_bDying = true;
}

void JewelObject::doDyingAnimation()
{
  //@todo
}



bool JewelObject::isFalling() const
{
  return m_isFalling;
}

void JewelObject::setFalling(bool falling)
{
  m_isFalling = falling;
}

