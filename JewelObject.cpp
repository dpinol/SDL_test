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

const short JewelObject::FALLING_STEPS = 100;

JewelObject::JewelObject(Jewel &jewel, bool firstRow) :
  m_model(&jewel),
  m_fallingStep(0)
{
  if (firstRow)
    m_bDead = true;
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
  //pending dying animation
  if(getModel().getColor() != Jewel::NO_COLOR && !isDying()) // && !isDead())
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_pixel.getX(), (Uint32)m_pixel.getY(),
                                          m_width, m_height, m_currentRow, getModel().getColor());
  //TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void JewelObject::update()
{
  if (isDying())
  {
    m_dyingCounter++;
    if (m_dyingCounter == m_dyingTime)
    {
      m_bDead = true;
      m_bDying = false;
    }
  } else if (isFalling())
  {
    fallStep();
  }

}


void JewelObject::setMovement(JewelMove const &m)
{

}


void JewelObject::resurrect()
{
  m_bDying = false;
  m_bDead = false;
  getModel().setColor(random() % Jewel::NUM_COLORS);
}

void JewelObject::kill()
{
  m_bDying = true;
  m_dyingTime = 10;
  m_dyingCounter = 0;
}

void JewelObject::doDyingAnimation()
{
  //@todo
}


void JewelObject::resetFalling()
{
  m_fallingStep = 0;
}

bool JewelObject::isFalling() const
{
  return m_fallingStep != 0;
}

bool JewelObject::isFallDone() const
{
  return m_fallingStep >= FALLING_STEPS;
}

void JewelObject::fallStep()
{
  m_fallingStep++;
  getPixel().setY(getPixel().getY() + float(HEIGHT) / FALLING_STEPS); //jo.getFallingStep() *
  //if (m_fallingStep == FALLING_STEPS)
  //  m_fallingStep = 0;
}

