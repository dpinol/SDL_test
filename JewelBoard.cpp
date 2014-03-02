//
//  JewelBoard.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 26/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#include "JewelBoard.h"
#include "JewelObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "utils/utils.h"
#include <assert.h>

JewelBoard::JewelBoard() : BoardObject()
{
  count = 0;
  maxcount = 10;

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels", TheGame::Instance()->getRenderer());

  createInialJewelsBoard();
}

void JewelBoard::createInialJewelsBoard()
{
  for (unsigned i = 1 ; i < BoardPos::BoardPos::SIZE ; ++i)
  {
    for (unsigned j = 0 ; j < BoardPos::BoardPos::SIZE ; ++j)
    {
      m_jewels[i][j] = new JewelObject(rand() % kJewelsColors);
    }
  }
}

void JewelBoard::load(std::unique_ptr<LoaderParams> const &pParams)
{
  BoardObject::load(std::move(pParams));
  m_scrollSpeed = pParams->getAnimSpeed();

  m_scrollSpeed = 1;

  m_srcRect1.x = 0;
  m_destRect1.x = m_pixel.getX();
  m_srcRect1.y = 0;
  m_destRect1.y = m_pixel.getY();

  m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
  m_srcRect1.h = m_destRect1.h = m_height;

  m_srcRect2.x = 0;
  m_destRect2.x = m_pixel.getX() + m_width;
  m_srcRect2.y = 0;
  m_destRect2.y = m_pixel.getY();

  m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
  m_srcRect2.h = m_destRect2.h = m_height;
}

/******* Model *******/
#ifdef NDEBUG
inline void assertBoardPos(BoardPos const)
{
}
#else
inline void assertBoardPos(BoardPos const pos)
{
  if (!pos.isValid())
    throw std::runtime_error("BoardPos " + dani::toString(pos) + "is not valid");
}
#endif

JewelObject& JewelBoard::getJewel(BoardPos const pos)
{
  assertBoardPos(pos);
  return *m_jewels[pos.m_row][pos.m_col];
}

JewelObject const& JewelBoard::getJewel(BoardPos const pos) const
{
  assertBoardPos(pos);
  return *m_jewels[pos.m_row][pos.m_col];
}





/******* Model *******/


void JewelBoard::draw()
{
  // draw first rect
  SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), TheTextureManager::Instance()->getTextureMap()[m_textureID], &m_srcRect1, &m_destRect1, 0, 0, SDL_FLIP_NONE);

  // draw second rect
  SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), TheTextureManager::Instance()->getTextureMap()[m_textureID], &m_srcRect2, &m_destRect2, 0, 0, SDL_FLIP_NONE);
  forAll([&](JewelObject &jewel)
  {
    jewel.draw();
  });
}
void JewelBoard::update()
{
  if(count == maxcount)
  {
    // make first rectangle smaller
    m_srcRect1.x += m_scrollSpeed;
    m_srcRect1.w -= m_scrollSpeed;
    m_destRect1.w -= m_scrollSpeed;

    // make second rectangle bigger
    m_srcRect2.w += m_scrollSpeed;
    m_destRect2.w += m_scrollSpeed;
    m_destRect2.x -= m_scrollSpeed;

    // reset and start again
    if(m_destRect2.w >= m_width)
    {
      m_srcRect1.x = 0;
      m_destRect1.x = m_pixel.getX();
      m_srcRect1.y = 0;
      m_destRect1.y = m_pixel.getY();

      m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
      m_srcRect1.h = m_destRect1.h = m_height;

      m_srcRect2.x = 0;
      m_destRect2.x = m_pixel.getX() + m_width;
      m_srcRect2.y = 0;
      m_destRect2.y = m_pixel.getY();

      m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
      m_srcRect2.h = m_destRect2.h = m_height;
    }
    count = 0;
  }

  count++;

  for (unsigned i = 1 ; i < BoardPos::BoardPos::SIZE ; ++i)
  {
    for (unsigned j = 0 ; j < BoardPos::BoardPos::SIZE ; ++j)
    {
      m_jewels[i][j]->update();
    }
  }
}

void JewelBoard::clean()
{
  for (unsigned i = 1 ; i < BoardPos::BoardPos::SIZE ; ++i)
  {
    for (unsigned j = 0 ; j < BoardPos::BoardPos::SIZE ; ++j)
    {
      m_jewels[i][j]->clean();
    }
  }

  BoardObject::clean();
}
