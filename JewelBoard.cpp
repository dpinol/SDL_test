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
#include <algorithm>



#include <SDL_events.h>

JewelBoard::JewelBoard() : BoardObject(),
  m_model(*this),
  m_offset(350, 100),
  m_bottomDown(m_offset + Vector2D(JewelObject::WIDTH * BoardPos::NUM_COLS, JewelObject::HEIGHT * (BoardPos::NUM_ROWS + 1)) ),
  m_drag(*this)
{

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels", TheGame::Instance()->getRenderer());

  createInitialJewelsBoard();
}


void JewelBoard::createInitialJewelsBoard()
{
  forAllPos([&](BoardPos const pos)
  {
    Jewel &jewel = m_model.getJewel(pos, true);
    JewelObject *jo = new JewelObject(jewel, pos.m_row == 0);

    m_jewels[pos.m_row][pos.m_col] = jo;
    Vector2D pixel = getJewelPixel(pos);
    jo->getPixel() = pixel;
  });
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
    //if (jewel.getPixel().getY() +  jewel.getHeight() >= m_offset.getY())
    if (!jewel.isDead())
      jewel.draw();
  });
}

Vector2D JewelBoard::getJewelPixel(BoardPos pos) const
{
  return Vector2D(m_offset.getX() + JewelObject::WIDTH * pos.m_col,
                  m_offset.getY() + JewelObject::HEIGHT * pos.m_row);
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

void JewelBoard::pureSwap(BoardPos pos, BoardPos pos2)
{
  /*getJewel(BoardPos(pos.m_col, pos.m_row + 1)) = jo;
  getJewel(BoardPos(pos.m_col, pos.m_row)).resetFalling();*/
  std::swap( m_jewels[pos.m_row][pos.m_col], m_jewels[pos2.m_row][pos2.m_col]);
}

void JewelBoard::shiftDown(BoardPos pos)
{
  //JewelObject &jo = getJewel(pos);
  assert(pos.m_row < BoardPos::NUM_ROWS);
  {
    BoardPos next = pos.getBelow();
    LOG_INFO("swapping " << pos << " with " << next);

    pureSwap(pos, next);
    m_model.pureSwap(pos, next);
    //it will be set to falling again if lower jewel is detected to be empty
    getJewel(next).resetFalling();
    getJewel(pos).resetFalling();
  }
  /*  else
  {
    BoardPos first(pos.m_col, 0);
    pureSwap(pos, first);
    jo.resetFalling();
  }

   m_jewels[fallPos.m_row][fallPos.m_col] = m_jewels[fallPos.m_row - 1][fallPos.m_col];*/
  /*  JewelObject &jo = getJewel(pos);
  //it will be reset to falling if lower jewel is detected to be empty
  jo.resetFalling();
  if (pos.m_row < BoardPos::NUM_ROWS)
    getJewel(BoardPos(pos.m_col, pos.m_row + 1)).getModel() = jo.getModel();
  else
  {
    BoardPos fallPos(pos.m_col, BoardPos::NUM_ROWS);
    JewelObject &last = getJewel(fallPos);
    while(fallPos.m_row > 0)
    {
      m_jewels[fallPos.m_row][fallPos.m_col] = m_jewels[fallPos.m_row - 1][fallPos.m_col];
      fallPos.m_row--;
    }
    m_jewels[0][fallPos.m_col] = &last;
    m_jewels[0][fallPos.m_col]->getModel().setColor(random() % Jewel::NUM_COLORS);
  }
  */
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
    if (jo.isFallDone())
      shiftDown(pos);
    if (pos.m_row > 0 && (jo.isFalling() || jo.isDead()))
    {
      BoardPos const upperPos = BoardPos(pos.m_col, pos.m_row - 1);
      JewelObject &upper = getJewel(upperPos);
      upper.fallStep();
      //resurrect so that it will fall
      if (pos.m_row == 1 && upper.isDead())
      {
        LOG_INFO("Resurrecting " << upperPos);
        upper.resurrect();
        upper.getPixel() = getJewelPixel(upperPos);
      }

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
