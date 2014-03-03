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
  m_bottomDown(m_offset + Vector2D(JewelObject::WIDTH, JewelObject::HEIGHT) * BoardPos::SIZE )
{

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels", TheGame::Instance()->getRenderer());

  createInitialJewelsBoard();
}

void JewelBoard::createInitialJewelsBoard()
{
  for (unsigned i = 0 ; i <= BoardPos::BoardPos::SIZE ; ++i)
  {
    for (unsigned j = 0 ; j < BoardPos::BoardPos::SIZE ; ++j)
    {
      Jewel &jewel = m_model.getJewel(BoardPos(j, i));
      JewelObject *jo = new JewelObject(jewel);
      m_jewels[i][j] = jo;
      jo->getPixel().setX(m_offset.getX() + jo->getWidth() * j);
      jo->getPixel().setY(m_offset.getY() + jo->getHeight() * i);
    }
  }
}

void JewelBoard::kill(BoardPos pos)
{

}

void JewelBoard::load(std::unique_ptr<LoaderParams> const &pParams)
{
}

/******* Model *******/
#ifdef NDEBUG
inline void assertBoardPos(BoardPos const)
{
}
#else
inline void assertBoardPos(BoardPos const pos)
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
  Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();
  bool clicked = TheInputHandler::Instance()->getMouseButtonState(LEFT);
  if (clicked)
  {
    if (!m_dragging.isValid())
      m_dragging = getJewelAt(pMousePos);
  }
  else
  {
    if (m_dragging.isValid() && !TheInputHandler::Instance()->getMouseButtonState(LEFT))
    {
      BoardPos const dropping = getJewelAt(pMousePos);
      if (dropping.isValid() && (m_dragging - dropping).isDirection())
        swap(m_dragging, dropping);
      else
        LOG_DEBUG("Swap not valid because dropping outside grid or too far");
    }
    m_dragging = BoardPos();
  }

  /*
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      m_dragging = getJewelAt(event.button);
      break;
    case SDL_MOUSEBUTTONUP:
      BoardPos const dropping = getJewelAt(event.button);
      if (m_dragging.isValid()
          && dropping.isValid() && dropping.isDirection())
      {
        swap(m_dragging, dropping);
      }
      break;

    }
  }
*/
  forAll([&](JewelObject &jewel)
  {
    jewel.update();
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
