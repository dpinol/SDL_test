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

JewelBoard::JewelBoard() : BoardObject(), m_model(*this)
{

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels", TheGame::Instance()->getRenderer());

  createInialJewelsBoard();
}

void JewelBoard::createInialJewelsBoard()
{
  for (unsigned i = 0 ; i <= BoardPos::BoardPos::SIZE ; ++i)
  {
    for (unsigned j = 0 ; j < BoardPos::BoardPos::SIZE ; ++j)
    {
      m_jewels[i][j] = new JewelObject(rand() % kJewelsColors);
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
  forAll([&](JewelObject &jewel)
  {
    jewel.draw();
  });
}
void JewelBoard::update()
{
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
