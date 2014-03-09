/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

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

JewelBoard::JewelBoard(Board &board):
  m_model(board),
  m_offset(342, 86),
  m_size(JewelObject::WIDTH * BoardPos::NUM_COLS, JewelObject::HEIGHT * (BoardPos::NUM_ROWS + 1) ),
  m_drag(*this),
  m_strike(m_model, this),
  m_jewelsFalling(true)
{
  board.setCallback(this);

  TheTextureManager::Instance()->load("assets/jewels.png", "jewels");

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

bool JewelBoard::isAlive(BoardPos pos) const
{
  return !getJewel(pos).isDead() && !getJewel(pos).isDying();
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

Board const &JewelBoard::getModel() const
{
  return m_model;
}

Board &JewelBoard::getModel()
{
  return m_model;
}

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
  forAllPos([&](BoardPos const &pos)
  {
    JewelObject &jewel = getJewel(pos);
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
  if (!v.isInside(m_offset, m_offset + m_size))
    return BoardPos();
  return BoardPos((v.getX() - m_offset.getX()) / JewelObject::WIDTH,
                  (v.getY() - m_offset.getY()) / JewelObject::HEIGHT);
}

/**
 * @brief wa swaps jewels at specified positions
 * but only if final position achieves a strike
 * @param pos1
 * @param pos2
 * @return whether they could be swap

bool swap(BoardPos const pos1, BoardPos const pos2);

bool JewelBoard::swap(BoardPos const pos1, BoardPos const pos2)
{
  JewelSwap sw(m_model);
  sw.setPositions(pos1, pos2);
  return sw.run();
}
*/
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
    //@bug still would rarely fails.pending to investigate
    //assert(getJewel(next).isDead());
    LOG_DEBUG("jewel " << next << " popped up ");

    pureSwap(pos, next);
    m_model.pureSwap(pos, next);

    //it will be set to falling again if lower jewel is detected to be empty
    getJewel(next).setFalling(false);
    getJewel(pos).setFalling(false);
  }
}


void JewelBoard::update()
{
  //@todo should we block while block are falling?
  bool clicked = TheInputHandler::Instance()->getMouseButtonState(LEFT);
  if (clicked)
    m_drag.drag();
  else
    m_drag.drop();

  m_model.update();
  m_jewelsFalling = false;
  forAllPos([&](BoardPos pos)
  {
    JewelObject &jo = getJewel(pos);
    if (jo.isFallDone())
      shiftDown(pos);
    if (pos.m_row > 0 && !jo.isDying() && (jo.isFalling() || jo.isDead()))
    {
      m_jewelsFalling = true;
      BoardPos const upperPos = BoardPos(pos.m_col, pos.m_row - 1);
      JewelObject &upper = getJewel(upperPos);
      if (!upper.isFalling())
      {
        upper.setFalling();
        //resurrect so that it will fall
        if (pos.m_row == 1 && upper.isDead())
        {
          LOG_INFO("Resurrecting " << upperPos);
          upper.resurrect();
          upper.getPixel() = getJewelPixel(upperPos);
        }
      }

    }
    jo.update();
  });

  if (!m_jewelsFalling)
  {
    //mostly works, but eventually a falling jewel overtakes lower one and assert at shiftDown fails
    //or jewels stop at halfway
    forAllPos([&](BoardPos pos)
    {
      m_strike.findMatch(pos, getJewel(pos).getModel().getColor());
    }, false);
  }
}

void JewelBoard::clean()
{
  forAll([&](JewelObject &jewel)
  {
    jewel.clean();
  });

  GameObject::clean();
}
