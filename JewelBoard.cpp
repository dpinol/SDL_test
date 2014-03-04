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
#include "InputHandler.h"
#include "Game.h"
#include <model/JewelSwap.h>
#include "utils/utils.h"
#include "utils/log.h"
#include <assert.h>

#include <SDL_events.h>

JewelBoard::JewelBoard() : BoardObject(),
  m_model(*this),
  m_offset(350, 100),
  m_bottomDown(m_offset + Vector2D(JewelObject::WIDTH * BoardPos::NUM_COLS, JewelObject::HEIGHT * BoardPos::NUM_ROWS + 1) ),
  m_drag(*this)
{

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels", TheGame::Instance()->getRenderer());

  createInitialJewelsBoard();
}

void JewelBoard::createInitialJewelsBoard()
{
  for (unsigned y = 0 ; y <= BoardPos::BoardPos::NUM_ROWS ; ++y)
  {
    for (unsigned x = 0 ; x < BoardPos::BoardPos::NUM_COLS ; ++x)
    {
      Jewel &jewel = m_model.getJewel(BoardPos(x, y), true);
      JewelObject *jo = new JewelObject(jewel);
      m_jewels[y][x] = jo;
      jo->getPixel().setX(m_offset.getX() + jo->getWidth() * x);
      jo->getPixel().setY(m_offset.getY() + jo->getHeight() * y);
    }
  }
}

void JewelBoard::kill(BoardPos pos)
{
  getJewel(pos).kill(); //.setColor(Jewel::NO_COLOR);
}

void JewelBoard::load(std::unique_ptr<LoaderParams> const &pParams)
{
  //@todo load dimensions from xml
}

/******* Model *******/
#ifdef NDEBUG
inline static void assertBoardPos(BoardPos const)
{
}
#else
inline static void assertBoardPos(BoardPos const pos)
{
  if (!pos.isValid(true))
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
  forAll([&](JewelObject &jewel)
  {
    if (jewel.getPixel().getY() +  jewel.getHeight() >= m_offset.getY())
      jewel.draw();
  });
}

BoardPos JewelBoard::getJewelAt(Vector2D const &v) const
{
  if (!v.isInside(m_offset, m_bottomDown))
    return BoardPos();
  return BoardPos((v.getX() - m_offset.getX()) / JewelObject::WIDTH,
                  (v.getY() - m_offset.getY()) / JewelObject::HEIGHT);
}

bool JewelBoard::swap(BoardPos const pos1, BoardPos const pos2)
{
  JewelSwap sw(m_model);
  sw.setPositions(pos1, pos2);
  return sw.run();
}



void JewelBoard::update()
{
  bool clicked = TheInputHandler::Instance()->getMouseButtonState(LEFT);
  if (clicked)
    m_drag.drag();
  else
    m_drag.drop();

  m_model.update();
  forAllPos([&](BoardPos pos)
  {
    JewelObject &jo = getJewel(pos);
    if ((jo.isFalling() || jo.isDead()) && pos.m_row < BoardPos::NUM_ROWS)
    {
      getJewel(BoardPos(pos.m_col, pos.m_row + 1)).setFalling(true);
    }
    jo.update();
  });
}

void JewelBoard::clean()
{
  forAll([&](JewelObject &jewel)
  {
    jewel.clean();
  });

  BoardObject::clean();
}
