/**************************************************************************
** Qt Creator license header template
**   Special keywords: dpinol 03/03/2014 2014
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#include "JewelDrag.h"
#include "JewelObject.h"
#include "JewelBoard.h"
#include <utils/log.h>
#include <utils/Effect.h>
#include "InputHandler.h"

JewelDrag::JewelDrag(JewelBoard &board)
  :m_board(board),
    m_modelSwap(board.getModel()),
    m_swapEffect(NULL)
{
}

void JewelDrag::update()
{

}

void JewelDrag::drag()
{
  Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();

  if (!m_fromPixel.isValid())
  {
    //drag start
    BoardPos pos = m_board.getJewelAt(pMousePos);
    if (pos.isValid())
    {
      m_fromPixel = pMousePos;
      m_fromPos = pos;
    }
  }
  else
  {
    //move jewel only vertical or horizontal
    Vector2D shift = pMousePos - m_fromPixel;
    BoardPos shiftPos;
    int RATIO = 3;
    if (shift.getX() > JewelObject::WIDTH / RATIO)
      shiftPos = BoardPos(1,0);
    else if (shift.getX() < -JewelObject::WIDTH / RATIO)
      shiftPos = BoardPos(-1,0);
    else if (shift.getY() > JewelObject::HEIGHT / RATIO)
      shiftPos = BoardPos(0, 1);
    else if (shift.getY() < -JewelObject::HEIGHT / RATIO)
      shiftPos = BoardPos(0, -1);
    else
    {
      LOG_DEBUG("shift too small: " << shift);
      return;
    }
    LOG_DEBUG("shift: " << shift);
    m_toPos = m_fromPos + shiftPos;
    bool returnBack;
    if (m_toPos.isValid())
    {
      m_modelSwap.setPositions(m_fromPos, m_toPos);
      returnBack = m_modelSwap.isValid();

      m_board.getJewel(m_fromPos).swapWith(shiftPos, returnBack);
      m_swapEffect = &m_board.getJewel(m_toPos).swapWith(-shiftPos, returnBack);
      m_swapEffect->setNext([&]()
      {
        m_modelSwap.run();
        m_swapEffect->setNext(NULL);
      });
    }
    else
      LOG_DEBUG("to_pos not valid: " << m_toPos);
  }
}

void JewelDrag::drop()
{
  m_fromPixel.clear();
  m_fromPos.clear();
  /*
  Vector2D const &pMousePos = TheInputHandler::Instance()->getMousePosition();
  if (m_dragging.isValid() && !TheInputHandler::Instance()->getMouseButtonState(LEFT))
  {
    BoardPos const dropping = getJewelAt(pMousePos);
    if (dropping.isValid() && (m_dragging - dropping).isDirection())
      swap(m_dragging, dropping);
    else
      LOG_DEBUG("Swap not valid because dropping outside grid or too far");
  }
  m_dragging = BoardPos();
  */
}


