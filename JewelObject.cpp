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
#include <utils/ValueEffect.h>
#include <utils/log.h>

const short JewelObject::FALLING_STEPS = 20;

JewelObject::JewelObject(Jewel &jewel, bool firstRow) :
  m_model(&jewel),
  m_fallingStep(0)
{
  m_swapper.setVerbose(true);
  m_effects->addChild(m_swapper);
  m_effects->addChild(m_dier);

  m_swapper.setPeriod(3000);
  m_swapper.setPaused(true);
  m_dier.setPaused(true);

  m_bfalling = false;
  if (firstRow)
    m_bDead = true;
  m_pixel = Vector2D(0,0);
  m_currentRow = 0;
  //we don't use it so far
  m_currentFrame = -1; //jewel.getColor();

  // get drawing variables
  m_width = SPRITE_SIZE;
  m_height = SPRITE_SIZE;
  m_textureID = "jewels";
}

Jewel& JewelObject::getModel()
{
  return *m_model;
}

dani::Effect &JewelObject::swapWith(BoardPos relativeShift, bool andReturn)
{
  m_swapper.setPaused(false);
  Vector2D vShift(relativeShift.m_col * WIDTH, relativeShift.m_row * HEIGHT);
  m_swapper.setMean({0,0}, vShift);
  m_swapper.setStartPhase(0);
  if (andReturn)
  {
    m_swapper.setStopPhase(M_PI);
  }
  else
  {
    m_swapper.setStopPhase(M_PI / 2);
  }
  return m_swapper;
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
  int alpha = 255;
  //if (isDying())
  //  alpha = 255.0 * (m_dyingTime - m_dyingCounter) / m_dyingTime;
  if(getModel().getColor() != Jewel::NO_COLOR) // && !isDead())
  {
    Uint32 x = (Uint32)m_pixel.getX() + MARGIN;
    Uint32 y = (Uint32)m_pixel.getY() + MARGIN;

    if (!m_swapper.isDone() && !m_swapper.isPaused())
    {
      Vector2D swapper = m_swapper.get();
      x += swapper.getX();
      y += swapper.getY();
      LOG_DEBUG("swapper in action" << getPixel() << " " << swapper << "col " <<getModel().getColor());
    }

    TextureManager::Instance()->drawFrame(m_textureID, x, y,
                                          m_width, m_height, m_currentRow, getModel().getColor(),
                                          NULL, 0, alpha);
  }
  //TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void JewelObject::update()
{
  m_effects->update();
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
  //@todo we should allow direct strike. fo
  getModel().setColor(random() % Jewel::NUM_COLORS);
}

void JewelObject::kill()
{
  if (!m_bDying)
  {
   // m_model->setColor(Jewel::NO_COLOR);
    m_bDying = true;
    m_dyingTime = 60;
    m_dyingCounter = 0;
    m_fallingStep = 0;
  }
}


void JewelObject::setFalling(bool falling)
{
  m_bfalling = falling;
  m_fallingStep = 0;
}

bool JewelObject::isFalling() const
{
  return m_bfalling; //m_fallingStep != 0;
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

